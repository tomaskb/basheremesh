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

#define LOGFILE "runcmd.log"
#define EXECYES 0
#define EXECFAIL 1

int go_on = 1;

void finish (void)
{
  go_on = 0;
}

/* Run 'command' and redirects standard streams to open descriptors stored in the integer vector 'io'.
   Compare the subprocess' execution results collected by 'runcmd' with those passed as arguments.
   If they match, return true; otherwise return false. */

int tryrun (const char *command,  int *io, int correct_termination, int correct_exit_status, int execresult)
{
  int pid, nbytes, test, count;
  int result;
  char *command_line;

  /* Needed because we'll change 'command'. */
  command_line = malloc ((strlen(command) * sizeof(char))+1);
  sysfatal (!command_line);
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
	    IS_NORMTERM(&result) ? "normally" : "abnormally", 
	    IS_NORMTERM(&result) ? (EXITSTATUS(&result) == EXIT_SUCCESS ? "and sucessfully" : "and unsucessfully") :  "",
	    EXITSTATUS(&result), &nbytes);
    
    test =  (EXITSTATUS(&result) == correct_exit_status) 
      && (IS_NORMTERM(&result) == correct_termination);
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
  sysfatal ((io[0] = open ("/dev/null", O_WRONLY)) <0);
  sysfatal ((io[1] = open ("/dev/null", O_WRONLY)) <0);
  sysfatal ((io[2] = open ("/dev/null", O_WRONLY)) <0);

  result +=tryrun (cmd1, io, 1, 0, EXECYES);   /* Normal, success. */
  result +=tryrun (cmd2, io, 0, 0, EXECYES);   /* Abnormal, any.   */
  result +=tryrun (cmd3, io, 1, 2, EXECYES);   /* Normal, failure. */

  return result;		/* REMOVE THIS LINE TO COMPLETE THE TESTS. */

  /* Test redirection. */

  sysfatal ((fd = open ("in.txt", O_CREAT | O_TRUNC | O_RDWR,  S_IRUSR | S_IWUSR)) <0);
  write (fd, "a", 1);
  sysfatal(close(fd)<0);

  sysfatal ((io2[0] = open ("in.txt", O_RDONLY)) <0);
  sysfatal ((io2[1] = open ("out.txt", O_CREAT | O_TRUNC | O_RDWR,  S_IRUSR | S_IWUSR)) <0);
  sysfatal ((io2[2] = open ("err.txt", O_CREAT | O_TRUNC | O_RDWR,  S_IRUSR | S_IWUSR)) <0);


  /* cmd, io, term, exit, exec */

  result +=tryrun (cmd4, io2, 1, 0, EXECYES);   /* Normal, success. */

  /* Test nonblock. */

  result +=tryrun (cmd5, io2, 1, 0, EXECFAIL);   /* Normal, success. */

  /* Test whether exec failed. */

  result +=tryrun (cmd6, io, 1, 0, EXECYES);   /* Normal, success. */

  return result;
}
