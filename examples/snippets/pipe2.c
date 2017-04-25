/* pipe2 - Another pipe example, with redirection.

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
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <posixeg/debug.h>

#define MAX_SIZE 1024

int main (int argc, char **argv)
{
  int pid, status, nbytes;
  char buffer[MAX_SIZE];
  int pipefd[2], ret;

  char *command_line[] = {"date", NULL};

  /* Create a pipe and return two new file descriptors:
     pipefd[0] is the 'input' descriptor, or the 'reading end' of the pipe;
     pipefd[1] is the 'ouput' descriptor, or the 'writing end'of the pipe.
     
     In this present exemple, pipefd[0] == 3, and pipefd[1] == 4. */
  
  ret = pipe (pipefd);
  sysfatal (ret < 0);

  /* Now fork. */

  pid = fork ();
  sysfatal (pid <0);

  if (pid >0)
    {
      printf ("P: waiting for child\n");
      wait (&status);		/* Wait for child to terminate. */
      nbytes = read (pipefd[0], buffer, 255); /* Read from pipe. */
      buffer[nbytes] = '\0';
      printf ("P: Child said %s\n", buffer);
    }
  else
    {
      /* Remember: the child process inherits the open file
	 descriptors. Therefore, it inherits pipefd. The pipe's buffer
	 is within the kernel, so both process have access to it
	 through the file descriptors.*/
      
      /*  The trick is the same used to redirect output to a rular file.
	  We close the standard output's descriptor (1) and duplicate the pipe's
	  writting end (4).  We end up with file descriptors 1 and 4 pointing
	  to the pipe writing end (output end).*/

      /* We should avoid having multiple file descriptors referring to the
         same file.  */

      close (1);
      dup (pipefd[1]);
      close (pipefd[1]);	/* We close file descriptor 4 (unused). */
      close (pipefd[0]);        /* We close also unused descriptor 3. */

      /* Now we exec the command. The new process will have the standard ouput
	 (descriptor 1) poiting to the pipe's writting end. The father process
	 can read from it.*/

      execvp (command_line[0], command_line);
    }


  return EXIT_SUCCESS;
}
