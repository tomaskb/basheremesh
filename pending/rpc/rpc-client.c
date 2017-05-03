/*  rpc-client.c - Very simple RPC client (lib)
    
    Copyright 2015  Francisco Jose Monaco   <moanco@icmc.usp.br>

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
#include <errno.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
#include <netdb.h>

#include <rpc.h>
#include <debug.h>

#define HOSTNAME "localhost"
#define PORT 5555

int confflag=0;
char config[CONFFIELDS][BUFFSIZE][BUFFSIZE];

void read_config (void)
{
  FILE *file;
  char name[BUFFSIZE], value[BUFFSIZE];
  int i;

  if (confflag)
    return;
  else
    confflag=1;

  i=0;

  file = fopen (CONFIGFILE,"r");
  sysfatal (!file);
  while ((i<CONFFIELDS) && (fscanf (file, "%s : %s", name, value) != EOF))
    {
      strncpy(config[i][0], name,  BUFFSIZE-1);
      strncpy(config[i][1], value, BUFFSIZE-1);
      i++;
    }
  
}

/* Get value of config field 'name'. */

char *getconf (const char* name)
{
  int i;
  i=0;
  while ( (i<CONFFIELDS) && (strcmp(config[i][0],name)))
    i++;
  if (i<CONFFIELDS)
    return config[i][1];
  else
    return NULL;
}

/*  Connect to server (hostname, port), call function 'string' and receive
    the reply in 'buffer'*/


void call_remote (const char *hostname, int port, char *string, char *buffer)
{
  struct sockaddr_in server_name;   
  int fd, rsc;
  struct hostent *hostinfo;
  FILE *file;

  fd = socket (AF_INET, SOCK_STREAM, 0); /* Create the socket */
  sysfatal(fd<0);
  
  server_name.sin_family = AF_INET;                  /* Internet family */
  server_name.sin_port = htons (PORT);               /* Port to listen to */

  /* Get host address from hostname. */
  hostinfo = gethostbyname (hostname);
  sysfatal (!hostinfo);

  server_name.sin_addr = *(struct in_addr *) hostinfo->h_addr_list[0];

  rsc = connect (fd, (struct sockaddr *) &server_name, sizeof (struct sockaddr));
  sysfatal (rsc<0);

  file = fdopen (fd, "w");
  sysfatal (!file);

  fprintf (file, "%s\r\n", string);
  fflush (file);
  read (fd, buffer, 1024);

  close (fd);
}

