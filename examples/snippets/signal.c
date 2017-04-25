/* signal.c - Example of signal handling (deprecated).

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
#include <signal.h>		/* For signals. */


typedef void (*sighandler_t) (int);

/* This is our signal handler. */

void say_hello (int num)
{
  printf (" Hello, got signal %d!\n", num);
}

int main (int argc, char **argv)
{
  sighandler_t result;

  /* We're telling the system that, instead of performing the standard
     action associated to SIGINT, we want the function say_hello to 
     be called. 

     Note that signal() is deprecated. 
     Use sigaction() instead (see example signal2.c) */

  result = signal (SIGINT, say_hello); /* SIGINT is Ctr-C */
  sysfatal (result == SIG_ERR);

  while(1);

  return EXIT_SUCCESS;
}
