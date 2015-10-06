/* myrpc-server-v02 - Very Simple RPC Server, vr. 01

   Copyright 2014  Monaco F. J.   <monaco@icmc.usp.br>

   This file is part of POSIXeg. 

    POSIXeg is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    POSIXeg is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with .  If not, see <http://www.gnu.org/licenses/>. 

*/

#include <stdio.h>		
#include <stdlib.h>		
#include <unistd.h>		/* read */
#include <sys/socket.h> 	/* socket, bind */
#include <arpa/inet.h>		/* htons */
#include <sys/select.h>		/* select */
#include <signal.h>		/* sigaction */
#include <sys/types.h>		/* waipid */
#include <sys/wait.h>		/* waipid */
#include <pthread.h>

#include "debug.h"		

#define PORT 5555		/* The well-known port. */
#define MAX_ARGS 1024		/* Max number of arguments. */
#define BUFFER_SIZE 1024	/* Max message length. */
#define DELAY 5			/* How long to delay (larger than timeout) */


/* Parser. */

int parse_args (char *buffer, char **args)
{
  int i;
  i=0; 
  do
    args[i] = strtok (i==0 ? buffer : NULL, " \t\r\n");
  while (args[i++]);
  args[i]=NULL;

  return i;
}

int msgcount ;			/* Count number of messages. */
typedef enum {nf_none=0, nf_lostrequest=3, nf_lostreply=5, nf_delay=7} netfault_t;

/* Worker thread. */

struct targ_t
{
  int fd;
  int client_id;
};

/* Worker thread. */

void * worker_thread (void *arg)
{
  int nbytes, new_fd;
  char buffer [BUFFER_SIZE];
  struct targ_t *targ;
  int pid, status, rsc;
  char *args[MAX_ARGS];

  targ = (struct targ_t *) arg;
  
  new_fd = targ->fd;
  
  do
    {

      nbytes = read (new_fd, buffer, BUFFER_SIZE-1);
      
      buffer[nbytes]=0; 
      
      if (nbytes>0)
	{
	  printf ("Message %u from client %u: %s", msgcount, targ->client_id, buffer);

	  /* Create a subprocess to execute external program (command). */
	  pid = fork();
	  sysfatal (pid<0);

	  if (pid>0) 		/* Original process (worker thread). */
	    {
	      wait (&status);
	      printf ("Requested command executed with status %d\n", WEXITSTATUS(status));
	      msgcount++;	      
	    }
	  else			/* Subprocess. */
	    {

	      /* Simulate lost request. */
	      if ((msgcount % nf_lostrequest)==0)
		{
		  printf ("Lost msg\n");
		  exit (0);
		}

	      parse_args (buffer, args);	      
	      
	      /* Restrict path to local directory (security). */
	      args [0] = strtok (args[0], "./");
	      printf ("Trying [%s]\n", args[0]);
	      rsc = setenv ("PATH", "./", 1); /*  */
	      sysfatal (rsc);

	      /* Simulate lost reply. */
	      if (msgcount % nf_lostreply)
		{
		  /* Redirect output. */
		  close (1);
		  dup (new_fd);
		  close (new_fd);
		}
	      else
		printf ("Lost reply\n");

	      /* Simulate delay. */
	      if ((msgcount % nf_delay)==0)
		{
		  fprintf (stderr, "Delayed request...");
		  fflush(stderr);
		  sleep (DELAY);
		  fprintf (stderr, "done\n");
		    }
	      
	      /* Execute command. */
	      rsc = execvp (args[0], args);
	      printf ("%s: %s\r\n", args[0], strerror(errno));
	      sysfatal (rsc<0);
	    }

	}
    }
  while (nbytes>0);		/* If client disconnects, we read returns 0. */

  pthread_exit (NULL);

  return NULL;
}

/* The main process. */

int main (int argc, char **argv)
{
  int fd, new_fd, rsc;  			
  struct sockaddr_in server_name, client_name;
  size_t size;
  struct targ_t targ;
#ifdef DEBUG
  int sockreuse;
#endif
  pthread_t cthread;


  /* Create the socket. */
  
  fd = socket (AF_INET, SOCK_STREAM, 0);
  sysfatal (fd<0);

  /* On debug, avoid TIME_WAIT. */
#ifdef DEBUG
  sockreuse = 1;
  rsc = setsockopt(fd,SOL_SOCKET,SO_REUSEADDR, &sockreuse, sizeof (sockreuse)); 
  sysfatal (rsc<0);
#endif


  /* Give the socket a name. */

  server_name.sin_family = AF_INET;                  /* Internet family */
  server_name.sin_port = htons (PORT);               /* Port to listen to */
  server_name.sin_addr.s_addr = htonl (INADDR_ANY);  /* Interface to listen to*/


  /* Bind the socket to the TCP address. */

  do
    {
      rsc = bind (fd, (struct sockaddr *) &server_name, sizeof (server_name));
      if (rsc<0)
	{
	  /* If we're TCP TIME_WAIT status, retry; otherwise, exit. */
	  sysfatal (errno != EADDRINUSE); 
	  fprintf (stderr, "%s. Retrying...\n", strerror(errno));
	  sleep(2);
	}
    }
  while (rsc<0);

  fprintf (stderr, "Server up and running on port %d\n", PORT);

  /* Start to listen to the socket on the given port. */
  
  rsc = listen (fd, 1);
  sysfatal (rsc<0);

  targ.client_id = 0;
  msgcount = 1;

  /* For eternity. */

  size = sizeof (client_name);

  while (1)
    {

      /* Accept connection request and get a new socket for the client.*/
      
      do
	new_fd = accept (fd, (struct sockaddr *) &client_name, (socklen_t*) &size);
      while ((new_fd<0) && (errno == EINTR));
      sysfatal (new_fd < 0);
      
      targ.client_id++;
      targ.fd = new_fd;

      fprintf (stderr,"Client %u connected from host %s, port %u\n",
	       targ.client_id, inet_ntoa (client_name.sin_addr),
	       ntohs (client_name.sin_port));
      
      pthread_create (&cthread, NULL, worker_thread, (void *) & targ);


    }
      
  close (fd);
  
  pthread_exit (NULL);

  return EXIT_SUCCESS;
}
