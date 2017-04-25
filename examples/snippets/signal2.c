/* signal2.c - Example of signal handling (with sigaction). 

   Copyright (c) 2015, Monaco F. J. <moanco@icmc.usp.br>

   This file is part of POSIX.

   POSIX is free software: you can redistribute it and/or modify
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


#include <posixeg/debug.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>		

/* This is our signal handler. */

void say_hello (int num)
{
  printf (" Hello, got signal %d!\n", num);
}

int main (int argc, char **argv)
{

  int result;		
  void *temp;
  struct sigaction act;		/* Signal handler structure. */

  /* The first step is to fill in the sigaction structure with
     appropriate values (man 2 sigaction).  Alternatively, we
     here just zero all the fields we don't need to adjust properly. */

  temp = memset(&act, 0, sizeof(struct sigaction));
  sysfatal (!temp);

  /* The only field of the sigaction structure we are interested
     is the pointer to the handler function. */

  act.sa_handler = say_hello;		   

  /* We're telling the system that, instead of performing the standard
     action associated to SIGINT (Ctr C), we want the function say_hello to 
     be called. */

  result = sigaction(SIGTSTP, &act, NULL); /* SIGTSTP is ^Z */
  sysfatal (result<0);

  while(1);			/* Remain here forever. */

  return EXIT_SUCCESS;
}
