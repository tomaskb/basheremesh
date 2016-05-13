/* t1.c - Test program 1

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
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

#include <debug.h>
#include "t1.h"

char buffer[T1_TOKENSIZE];


void giveup(int signun)
{
  fputs (buffer,stdout);
}

int main (int argc, char **argv)
{
  FILE *fp;
  int pid, val, rs;
  struct sigaction act;
  void *rp;

  /* Unless otherwise specified by further rules this programs returns
     the value it receives as its first argument converted to an integer. If no
     arguments are given, the program returns the default value T1_NOARG.*/

  if (argc > 1)
    val = atoi (argv[1]);
  else
    val = T1_NOARG;

  /* Save pid into a file. */

  pid = getpid();
  fp = fopen ("t1.log", "w");
  sysfatal (!fp);
  fprintf (fp, "%d\n", pid);
  fclose(fp);

  /* Cause a segmentation fault.*/

  if (val == T1_SEGFAULT)
    * ((int *) 0x0)  = 0;
  
  /* Read from stdin, write to stdout. */

  if (val == T1_MAKEIO)
    {

      rp = memset(&act, 0, sizeof(struct sigaction));
      sysfatal (!rp);
      act.sa_handler = giveup;		   
      rs = sigaction(SIGALRM, &act, NULL); 
      sysfatal (rs<0);



      alarm (3);
      fgets (buffer, T1_TOKENSIZE+1, stdin);
      if (!strcmp(buffer,T1_WRITETHIS))
	{
	  fputs (T1_READTHIS,stdout);
	  val = T1_IO;
	}
      else
	  fputs (buffer,stdout);
	
    }

  return val;

}
