/* runcommand.c - Execute a user-specified command as a subprocess. */

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <string.h>

#include <foo.h>
#include <debug.h>

void (*runcommand_onexit)(void) = NULL;

void runcommand_wait (int num, siginfo_t *info, void *ucontext)
{
  int status;
  wait (&status);
  if (runcommand_onexit)
    runcommand_onexit();
}

/* Execute a command in a subprocess as specified by argument 'command'. 
   See documentation of command_t for further information. */


int runcmd (char *command, int *result, int *io) 
{
  int pid, status; 
  int aux, i;
  char *args[CMD_MAX_ARGS]; 	

  *result = 0;

  /* Parse arguments. */

  i=0;
  args[i++] = strtok (command, CMD_DELIMITERS);
  while ((i<CMD_MAX_ARGS) && (args[i++] = strtok (NULL, CMD_DELIMITERS)));
  i--;

  pid = fork();
  fail (pid<0, -1);

  if (pid>0)			/* Parent (caller). */
    {
      aux = wait (&status);
      fail (aux<0, -1);
      
      if (WIFEXITED(status)) 
	*result |= NORMAL;
    }
  else				/* Child (subprocess). */
    {
      aux = execvp (args[0], args);
      fail (aux<0, -1);
      exit (-1);
    }
  return pid;			/* Only parent reaches this point. */
}
