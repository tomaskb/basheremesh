/* siginfo.c - Execute a command as a subprocess. 

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


#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>

#define MAXCOUNT 20

int count = MAXCOUNT;

void progressbar (void);
void showinfo (int n, siginfo_t *info, void *u);


int main (int argc, char **argv)
{
  struct sigaction act;

  memset (&act, 0, sizeof(struct sigaction)); /* Clear sigaction. */

  act.sa_flags |= SA_SIGINFO;	     /* Enable sigaction's siginfo. */
  act.sa_sigaction = showinfo;	     /* Set signale handler. */
  sigaction (SIGTSTP, &act, NULL);   /* Register SIGTSTP handler. */
  sigaction (SIGSEGV, &act, NULL);   /* Register SIGSEGV handler. */
  

  /* User instructions. */
  printf ("\n\n"
	  "Within %d seconds, either \n\n"
          "  at this terminal, press Ctr-Z or \n"
	  "  at another temrminal, issue kill -n SIGTSTP %d\n" 
	  "  otherwise, wait for a segfault.\n\n",
	  MAXCOUNT, getpid());

  progressbar();		/* Print a progress bar. */

  /* Count down. */

  count = MAXCOUNT;
  while (count--)
    {
      write (1,"-",1);
      sleep(1);
    }

  /* If we reach this point, force a segfault. */

  *( (int*) 0)=0;
  
  return 0;
}


/* Print progress bar. */
void progressbar (void)
{
  int i;
  for (i=write(0,"[",1); i<= MAXCOUNT   ; i+=write(0," ",1));
  for (i=write(0,"]",1); i<=(MAXCOUNT+1); i+=write(0,"\b",1));
}

/* This is the signal handler, we use it to exhibit some information
   about the received signal. Structure siginfo_t have many fields
   that can be inspect; this example uses only a few of them. See
   documentation of sigaction for further details. */

void showinfo (int n, siginfo_t *info, void *u)
{
  printf ("\n");
  switch(info->si_signo)	/* What signal did I receive? */
    {
    case SIGTSTP:
      printf ("Process would be suspended ");
      break;
    case SIGSEGV:
      printf ("Process referenced invalid memory ");
      break;
    default:
      printf ("This should not happen\n");
      exit(EXIT_FAILURE);
    }
  

  switch (info->si_code)	/* What caused the signal? */
    {
    case SI_USER:
      printf ("by the user (pid %d) (did you use kill ?))\n", 
	      info->si_pid);	/* Who send the signal? */
      break;
    case SI_KERNEL:
      printf ("by the kernel (did you press Ct-Z ?)\n");
      break;
    case SEGV_MAPERR:
    case SEGV_ACCERR:
      printf ("causing a segmentation fault\n");
      exit(1);
      break;
    default:
      printf ("due some reason (man sigaction)\n");
    }
   
  count = MAXCOUNT;
  progressbar();
}
