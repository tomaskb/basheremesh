/* rpipeline.c - Recursive implementation of a pipeline. 

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


#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <posixeg/debug.h>

#define NUM_COMMANDS 4			/* Number of commands in the pipeline. */

/* Recursive implementation of a pipepline execution. 
   You are strongly encouraged to devise an iterative implementation. */

void doit (char *cmd[][NUM_COMMANDS], int pipeA[2], int count)
{
  int pid, status, pipeB[2];

  if (cmd[0][0] != NULL)
    {

      sysfatal (pipe (pipeB)<0);

      pid = fork();
      sysfatal (pid<0);
      
      if (pid>0)			/* Parent: exec */
	{
	  if (cmd[1][0] != NULL) /* Not last, redirect input */
	    {
	      close (0);
	      dup (pipeB[0]);
	      close (pipeB[0]);
	    }
	  
	  if (count>0)		/* Not first, redirect output */
	    {
	      close (1);
	      dup (pipeA[1]);
	      close (pipeA[1]);
	    }

	  close (pipeB[1]);	/* Not used. PipeA[0] reived closed already.  */


	  execvp (cmd[0][0], cmd[0]);
	}
      else				/* Child: recurse */
	{
	  doit (&cmd[1], pipeB, ++count);
	  wait (&status);
	}
      
    }
}



int main (int argc, char **argv)
{
  /* Vector of argvs for: ls | grep .c | wc -l */

  char *cmd[][NUM_COMMANDS] = 	/* From last to first. */
   {
     {"wc", "-l", NULL}, 
     {"grep", ".c", NULL}, 
     {"ls", NULL}, 
     {NULL}			/* Null terminated. */
   };
  
  doit (cmd, NULL, 0);

  return EXIT_SUCCESS;
}
