/* test-runcmd - Program to test runcmd function

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
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <runcmd.h>
#include <debug.h>
#include "t1.h"


int noio[3]; /* Index 0,1,2 will be file descriptors to /dev/null. */

/* This wrapper function calls 

   pid = run runcmd(command, result, io) ;

   and returns pid. If io is NULL, standard streams are redirected to
   /dev/null before calling runcmd(), in order not to polute the console
   output; streams are restored before returning. This function also 
   outputs some basic information about the subprocess completion. */

int try_runcmd (const char* command, int *result, int *io)
{
  int pid, tio[3], tmp_result, nbytes;

  printf ("\nCommand %s%n", command, &nbytes);
  printf ("%*s", 20-nbytes, " ");

  /* Supress output if not redirecting. */
  if (!io)
    {
      tio[0]=dup(0); tio[1]=dup(1); tio[2]=dup(2);
      close (0); close(1); close (2);
      dup(noio[0]); dup(noio[1]); dup(noio[2]);
    }

  /* Run the command.*/

  pid = runcmd (command,  &tmp_result, io);

  /* Restore output if not redirecting. */
  if (!io)
    {
      close (0); close (1); close (2);
      dup(tio[0]); dup(tio[1]); dup(tio[2]);
      close (tio[0]); close(tio[1]); close (tio[2]);
    }

  /* Output basic information on subprocess completion. */

  printf ("(%5d, %8s, %3d, %3sblocking, exec %s)\n\n",
  	  pid,
  	  IS_NORMTERM(tmp_result) ? "normal" : "abnormal",
  	  EXITSTATUS(tmp_result),
  	  IS_NONBLOCK(tmp_result) ? "non" : "",
  	  IS_EXECOK(tmp_result) ? "success" : "failed");

  if (result)
    *result = tmp_result;

  return pid;

}

/* Returns 0 if check condition is met; returns 1 otherwise. 
   The function outputs OK or NO, respectively. */

int check (const char* message, int condition)
{
  int nbytes;
  printf ("   whether %s%n", message, &nbytes);
  printf ("%*s\n", 60-nbytes, condition ? "OK":"NO");
  return condition ? 0 : 1;
}

/* This program perform a series of tests and return the number of errors.*/

int main (int argc, char **argv)
{

  /* Macros to stringify a macro's integer value. */

#define _strfy(val) # val
#define  strfy(val) _strfy(val)

  /* Test cases. */

  char cmd1[] = "./t1" ;                        /* Exits T1_NOARG_EXIT. */
  char cmd2[] = "./t1 " strfy(T1_SOMEVALUE) ;   /* Exits T1_SOMEVALUE. */
  char cmd3[] = "./t1 " strfy(T1_SEGFAULT) ;    /* Causes segfault.   */
  char cmd4[] = "./nosuchfile";                 /* Causes exec failure. */
  char cmd5[] = "./t1 " strfy(EXECFAILSTATUS);  /* Exits EXECFAILSTATUS */
  char cmd6[] = "./t1"  strfy(T1_MAKEIO);	/* Make some IO. */

  int result, i, pid, io[3], rpid, nerrors, rs;
  FILE *fp;

  nerrors = 0;


  /* Disable standard streams if not redirecting. */

  sysfatal ((noio[0] = open ("/dev/null", O_WRONLY)) <0);
  sysfatal ((noio[1] = open ("/dev/null", O_WRONLY)) <0);
  sysfatal ((noio[2] = open ("/dev/null", O_WRONLY)) <0);

  /* Check  */

  pid = try_runcmd (cmd3, &result, NULL);   /* Normal, success. */
  printf ("  Checking...\n");

  nerrors += check ("abnormal termination is correctly reported", 
		    (!IS_NORMTERM(result)) && 
		    (EXITSTATUS(result) == 0));

  /* Check */


  pid = try_runcmd (cmd1, &result, NULL);   /* Normal, success. */
  printf ("  Checking...\n");

  fp = fopen ("t1.log", "r");
  sysfatal (!fp);
  fscanf (fp, "%d", &rpid);

  nerrors += check ("normal termination is correctly reported", 
		    IS_NORMTERM(result));

  nerrors += check ("pid is correctly returned on success", 
		    (IS_NORMTERM(result)) && 
		    (pid == rpid));

  nerrors += check ("exit status is correctly reported on sucess", 
		    (IS_NORMTERM(result)) &&
		    (EXITSTATUS(result) == 10));

  nerrors += check ("exec success if correctly reported", 
		    (IS_NORMTERM(result)) &&
		    (IS_EXECOK(result)));


  fclose (fp);
  unlink ("t1.log");

  /* Check  */

  pid = try_runcmd (cmd2, &result, NULL);   /* Normal, success. */
  printf ("  Checking...\n");

  nerrors += check ("command line arguments are correctly read", EXITSTATUS(result) == 11);

  /* Check */
  
  pid = try_runcmd (cmd4, &result, NULL);   /* Normal, success. */
  printf ("  Checking...\n");

  nerrors += check ("exec failure is correctly reported (a)", 
		    (!IS_EXECOK(result)) &&
		    (EXITSTATUS(result) == EXECFAILSTATUS));
  
  /* Check */
  
  pid = try_runcmd (cmd5, &result, NULL);   /* Normal, success. */
  printf ("  Checking...\n");

  nerrors += check ("exec failure is not reported on sucess (b)", 
		    (IS_EXECOK(result)) &&
		    (EXITSTATUS(result) == EXECFAILSTATUS));


  return nerrors;

}
