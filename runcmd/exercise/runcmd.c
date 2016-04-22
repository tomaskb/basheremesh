/* runcmd.c - Execute a command as a subprocess. 

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

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <string.h>

#include <runcmd.h>
#include <debug.h>


/* Execute 'command' in a subprocess. Information on the subprocess execution
   is stored in 'result' after its completion, and can be inspected with the
   aid of macros made available for this purpose. Argument 'io' is a pointer
   to an integer vector where the first, second and third positions store
   file descriptors to where standard input, output and error, respective, 
   shall be redirected; if NULL, no redirection is performed. Command line
   must be a string of blank separated arguments as if issued in a command
   line shell. For instance if 'command' is "program arg1 arg2 ... argN",  
   Arguments are parsed and associated to an argv vector such that argv[0]
   points to "program" and argv[N-1] points to "argN".  A member of the
   'exec' family of function is called to execute the program with the
   given arguments in a subprocess created by 'fork'.  Function 'runcmd'
   blocks until the subprocess terminates, unless the last argument in
   'command' starts with '&' (ampersand) character, in which case the 
   supbrocess is executed in parallel with the calling process.  In this 
   case, the function addressed by the global function pointer 
   'runcmd_onexig' is asynchronously called upon the subprocess termination
   (in response to SIGCHLD). If 'runcmd_onexig' points to NULL (default), 
   no action is performed.*/

int runcmd (char *command, int *result, int *io) /* ToDO: const char* */
{
  int pid, status; 
  int aux, i;
  char *args[RCMD_MAXARGS]; 	

  *result = 0;

  /* Parse arguments to obtain an argv vector. */

  i=0;
  args[i++] = strtok (command, RCMD_DELIM);
  while ((i<RCMD_MAXARGS) && (args[i++] = strtok (NULL, RCMD_DELIM)));
  i--;

  /* Create a subprocess. */

  pid = fork();
  sysfail (pid<0, -1);

  if (pid>0)			/* Caller process (parent). */
    {
      aux = wait (&status);
      sysfail (aux<0, -1);
      
      /* Collect termination mode. */
      if (WIFEXITED(status)) 
	*result |= NORMTERM;
    }
  else				/* Subprocess (child) */
    {
      aux = execvp (args[0], args);
      exit (EXECFAILSTATUS);
    }
  return pid;			/* Only parent reaches this point. */
}

/* If function runcmd is called in non-blocking mode, then function
   pointed by rcmd_onexit is asynchronously evoked upon the subprocess
   termination. If this variable points to NULL, no action is performed.
*/

void (*runcmd_onexit)(void) = NULL;

