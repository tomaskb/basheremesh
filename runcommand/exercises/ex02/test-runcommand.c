/* test-runcommand-v1 - Program to test runcommand function version 1. */

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

int tryrun (char **args,  int correct_exit_status, int correct_termination)
{
  int pid, nbytes, test;
  command_t command;


  /* Run the command.*/

  command.args = args;

  pid = runcommand (&command);
  

  printf ("%s %s (pid %d) terminated %s and %s (status %d) %n", 
	  args[0], args[1], pid, 
	  command.termination == NORMAL_TERMINATION ? "normally" : "abnormally", 
	  command.exit_status == EXIT_SUCCESS ? "sucessfully" : "unsucessfully", 
	  command.exit_status, &nbytes);

  test =  (command.exit_status == correct_exit_status) 
    && (command.termination == correct_termination);

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
  char *args3[] = {"./segfault", "", NULL};     /* Abnormal termination. */


  result = EXIT_SUCCESS;

  result |=tryrun (args1, 0, NORMAL_TERMINATION);
  result |=tryrun (args2, 2, NORMAL_TERMINATION);
  result |=tryrun (args3, EXIT_FAILURE, ABNORMAL_TERMINATION) ;
  return result;
}
