#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define NP 3
#define MAX 5

#define fatal(exp)   do{if (exp) {fprintf (stderr, "%s : %d : %s\n", __FILE__, __LINE__, \
					   strerror(errno));}} while(0)
   
int main ()
{
  int pid, i, fd[NP-1][2], status, rs;
  char *args[NP][MAX] =
    {
      {"ls", "-l", NULL},
      {"grep", "\"\\.c$\"", NULL},
      {"wc", "-l", NULL}
    };


  /* Create NP-1 pipes. */
  for (i=0; i<NP; i++)
    {
      rs = pipe(fd[i]);
      fatal (rs);
    }

  i=0;
  /* Fork NP processes. */
  while ( (i<NP) && (pid=fork()) )
    i++;
    
  /* Wait for the last subprocess. */
  if (pid>0)
    {
      waitpid (pid, &status, 0);
      fprintf (stderr, "Subprocess %d terminated\n", --i);
    }


  
  if (pid==0)
    {
      fprintf (stderr, "I'm subprocess %d\n", i);
      fprintf (stderr, "%d %s %d\n", (i-1), args[i][0], i);
      
      
      /* Except by the first subprocess, redirect input; */
      if (i>0)
      	{
      	  close (0);
      	  dup(fd[i-1][0]);
	  /* close (fd[i-1][0]); */
      	}

      /* Except by the last subprorcess, redirect output. */
      if (i<(NP-1))
      	{
      	  close (1);
      	  dup(fd[i][1]);
	  /* close (fd[i][1]); */
      	}

      execvp (args[i][0], args[i]);

      
    }


  return EXIT_SUCCESS;
}
