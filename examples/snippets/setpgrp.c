/* setpgrp.c - Set terminal control

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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <posixeg/debug.h>

void childterm (int n, siginfo_t *info, void *u)
{
  int status;
  printf ("Child pid %d terminated ", info->si_pid);
  wait (&status);
  if (WIFSIGNALED(status))
    printf ("by signal %d", WTERMSIG(status));
  printf ("\n");
}

void ttin (int n, siginfo_t *info, void *u)
{
  int status;
  printf ("Child pid %d signaled ", info->si_pid);
  wait (&status);
  if (WIFSIGNALED(status))
    printf ("with %d", WTERMSIG(status));
  printf ("\n");
}


int main (int argc, char **argv)
{
  struct sigaction act;
  pid_t pid;
  int rs, count;
  void *rp;
  char c;

  /* Handle child termination signal. */
  rp = memset(&act, 0, sizeof(struct sigaction)); /* Clear all. */
  sysfatal (!rp);
  act.sa_flags |= SA_SIGINFO;	     /* Enable sigaction's siginfo. */


  pid = fork();
  sysfatal (pid<0);

  if (pid>0)			/* Parent. */
    {
      act.sa_sigaction = childterm;	     /* Set signale handler. */
      rs = sigaction (SIGCHLD, &act, NULL);   /* Register SIGTSTP handler. */
      act.sa_sigaction = ttin;	     
      rs = sigaction (SIGTTIN, &act, NULL);   
      sysfatal (rs);
      while (1)
	{
	  write (1, "|", 2);
	  sleep (1);
	}
    }
  else				/* Child. */
    {

      act.sa_sigaction = childterm;	     /* Set signale handler. */
      rs = sigaction (SIGCHLD, &act, NULL);   /* Register SIGTSTP handler. */
      act.sa_sigaction = ttin;	     
      rs = sigaction (SIGTTIN, &act, NULL);   
      sysfatal (rs);

      /* mypid = getpid (); */
      setpgid(getpid(), 0);
      /* tcsetpgrp(1,getppid()); */

      count = 5;
      while (count--)
	{
	  sleep(3);
	  write (1, "-", 2);
	}
      read (0,&c, 1);
      exit (1);
    }

  return EXIT_SUCCESS;
}
