/* pipeline.c - Recursive implementation of a pipeline. 

   Copyright (c) 2015, Monaco F. J. <moanco@icmc.usp.br>

   This file is part of POSIXeg.

   POSIXeg is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published
   by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see
   <http://www.gnu.org/licenses/>.
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <posixeg/debug.h>

#define BUFFSIZE 1024
#define NARGS 1024

int main (int argc, char **argv)
{
  int pid, pipefd[2], status, rs;

  char *args[2][NARGS] =
    {
      {"ls", NULL},
      {"wc", "-l", NULL}
    };

  /* Create the pipe. */

  rs = pipe(pipefd);
  sysfatal (rs<0);

  /* Fork the first child. */

  pid = fork();
  sysfatal (pid<0);

  if (pid>0)			/* Parent. */
    {

      /* Fork the second child. */

      pid = fork();
      sysfatal (pid<0);

      if (pid>0)		/* Still parent. */
	{
	  close (pipefd[0]);	
	  close (pipefd[1]);
	  wait (&status);	
	}
      else			/* Second child (wc). */
	{
	  close (pipefd[1]);	
	  close (0);
	  dup (pipefd[0]);
	  close (pipefd[0]);

	  rs = execvp (args[1][0], args[1]); 
	  sysfatal (rs<0);
	}
      
      wait (&status);
    }
  else				/* First child (ls). */
    {
      close (pipefd[0]);
      close (1);
      dup (pipefd[1]);
      close (pipefd[1]);
      
      rs = execvp (args[0][0], args[0]);
      sysfatal (rs<0);
    }

  /* Only parent reaches this point. */
  return EXIT_SUCCESS;
}
