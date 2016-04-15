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
#define EXECYES 0
#define EXECFAIL 1

int go_on = 1;

void finish (void)
{
  go_on = 0;
}

/* Run the "program with arguments and return 0 on success or 1 on error. */

int tryrun (char *command,  int *io, int correct_termination, int correct_exit_status, int execresult)
{
  int pid, nbytes, test, count;
  int result;
  char *command_line;

  /* Needed because we'll change 'command'. */
  command_line = malloc ((strlen(command) * sizeof(char))+1);
  fatal (!command_line);
  strcpy (command_line, command);

  /* Run the command.*/

  runcmd_onexit = finish;

  pid = runcmd (command_line,  &result, io);


  if (pid==0)
    {
      printf ("%s (pid %d) execution failed %n", 
	      command, pid, &nbytes);
      test = execresult == EXECFAIL ? 0 : 1;
      printf ("%*s\n", 80-nbytes, test ? "NO" : "OK");
      return test;
    }
  
  if (IS_NONBLOCK(&result))
    {
      printf ("%s (pid %d) execution started asynchronously %n", 
	      command, pid, &nbytes);
      count =0;
      while (go_on)
	{
	  sleep(1);
	  count++;
	}
      test = (count == 2) ? 0 : 1;
      printf ("%*s\n", 80-nbytes, test ? "NO" : "OK");
      return test;
    }
  
    printf ("%s (pid %d) terminated %s  %s (status %d) %n", 
	    command, pid, 
	    IS_NORMAL(&result) ? "normally" : "abnormally", 
	    IS_NORMAL(&result) ? (EXITVALUE(&result) == EXIT_SUCCESS ? "and sucessfully" : "and unsucessfully") :  "",
	    EXITVALUE(&result), &nbytes);
    
    test =  (EXITVALUE(&result) == correct_exit_status) 
      && (IS_NORMAL(&result) == correct_termination);
    test = ! test;
    

    
    printf ("%*s\n", 80-nbytes, test ? "NO" : "OK");
    
    
    return test;
}


/* Main function: returns successfully if all tests are ok;
   returns unsucessfully otherwise. */

int main (int argc, char **argv)
{
  int result, fd;
  /* int count; */

  /* Test cases. */

  char cmd1[] = "ls runcmd.c" ;     /* File does exist. */
  char cmd2[] = "./segfault";       /* Abnormal termination. */
  char cmd3[] = "ls nosuchfile";    /* File does not exist. */
  char cmd4[] = "./io";  	    /* Test IO redirection. */
  char cmd5[] = "./nosuchfile";     /* Exec failed. */
  char cmd6[] = "./delay &";        /* Test nonblock. */

  int io[3], io2[3];

  result = EXIT_SUCCESS;
  result = 0;

  /* Disable standard streams for convenience. */
  fatal ((io[0] = open ("/dev/null", O_WRONLY)) <0);
  fatal ((io[1] = open ("/dev/null", O_WRONLY)) <0);
  fatal ((io[2] = open ("/dev/null", O_WRONLY)) <0);

  result +=tryrun (cmd1, io, 1, 0, EXECYES);   /* Normal, success. */
  result +=tryrun (cmd2, io, 0, 0, EXECYES);   /* Abnormal, any.   */
  result +=tryrun (cmd3, io, 1, 2, EXECYES);   /* Normal, failure. */

  return result;		/* REMOVE THIS LINE TO COMPLETE THE TESTS. */

  /* Test redirection. */

  fatal ((fd = open ("in.txt", O_CREAT | O_TRUNC | O_RDWR,  S_IRUSR | S_IWUSR)) <0);
  write (fd, "a", 1);
  fatal(close(fd)<0);

  fatal ((io2[0] = open ("in.txt", O_RDONLY)) <0);
  fatal ((io2[1] = open ("out.txt", O_CREAT | O_TRUNC | O_RDWR,  S_IRUSR | S_IWUSR)) <0);
  fatal ((io2[2] = open ("err.txt", O_CREAT | O_TRUNC | O_RDWR,  S_IRUSR | S_IWUSR)) <0);


  /* cmd, io, term, exit, exec */

  result +=tryrun (cmd4, io2, 1, 0, EXECYES);   /* Normal, success. */

  /* Test nonblock. */

  result +=tryrun (cmd5, io2, 1, 0, EXECFAIL);   /* Normal, success. */

  /* Test whether exec failed. */

  result +=tryrun (cmd6, io, 1, 0, EXECYES);   /* Normal, success. */

  return result;
}
