/* test-002.c - Program to test runcmd function

   Copyright (c) 2014, Francisco José Monaco <moanco@icmc.usp.br>

   This file is part of POSIXeg

   POSIXeg is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
    
*/



#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>

#include <runcmd.h>
#include <debug.h>

#include "t1.h"
#include "testutils.h"

int pipefd[2];

void * writepipe (void *arg)
{
  int rs=0;
  do 
    rs += write (pipefd[1], "abc", T1_TOKENSIZE);
  while ( (rs>0) && (rs<T1_TOKENSIZE) );

  sysfatal (rs<0);
  return NULL;
}

/* This program perform a series of tests and return the number of errors.*/

int main (int argc, char **argv)
{
  int nbytes;
  
  /* Test cases. */

  char cmd1[] = "./t1 " strfy(T1_MAKEIO);  /* Exits EXECFAILSTATUS */

  int result, pid, nerrors, rs, redirok, io[3];
  pthread_t thread;
  char buffer[4];

  nerrors = 0;

  /* Disable standard streams if not redirecting. */

  sysfatal ((noio[0] = open ("/dev/null", O_WRONLY)) <0);
  sysfatal ((noio[1] = open ("/dev/null", O_WRONLY)) <0);
  sysfatal ((noio[2] = open ("/dev/null", O_WRONLY)) <0);

  /* Check  */

  rs = pipe (pipefd);
  sysfatal (rs<0);

  pthread_create (&thread, NULL, writepipe, NULL);

  io[0] = pipefd[0];
  io[1] = pipefd[1];
  io[2] = fileno(stderr);

  pid = try_runcmd (cmd1, &result, io);   /* Normal, success. */
  printf ("  Checking...\n");

  nbytes = read (pipefd[0], buffer, 3);
  sysfatal (nbytes<0);

  buffer[3]=0;
  if (!strcmp(buffer,T1_READTHIS))
    redirok=1;
  else
    redirok=0;

  nerrors += check ("whether io is redirected correctly", redirok);

  
  pid = pid;

  return nerrors;

}
