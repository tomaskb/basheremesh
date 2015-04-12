/* test-runcommand-v1 - Program to test runcommand function version 1.

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

#include <foo.h>
#include <debug.h>

#define LOGFILE "foo.log"

/* Run the program with arguments and report results. */

int tryrun (char **args,  int correct_exit_status)
{
  int pid, nbytes, test;
  command_t command;

  /* Run the command.*/

  command.args = args;

  pid = runcommand (&command);
  

  printf ("%s %s (pid %d) terminated %s (status %d) %n", 
	  args[0], args[1], pid, 
	  command.exit_status == EXIT_SUCCESS ? "sucessfully" : "unsucessfully", 
	  command.exit_status, &nbytes);

  test =  (command.exit_status == correct_exit_status);

  printf ("%*s\n", 80-nbytes, test ? "OK" : "NO");

  return test;
}


/* Main function: returns successfully if all tests are ok;
   returns unsucessfully otherwise. */

int main (int argc, char **argv)
{
  int result;

  /* Test cases. */

  char *args1[] = {"ls", "runcommand.c", NULL}; /* File does exist. */
  char *args2[] = {"ls", "nosuchfile", NULL};   /* File does not exist. */

  result = EXIT_SUCCESS;

  result |=tryrun (args1, 0);
  result |=tryrun (args2, 2);

  return result;
}
