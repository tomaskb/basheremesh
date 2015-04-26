/* main.c - The foo shell

   Copyright (c) 2015, Monaco F. J. <moanco@icmc.usp.br>

   This file is part of POSIXeg.

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
#include <stdio.h>
#include <foosh.h>
#include <debug.h>

#define PROMPT "@:"

/* void test(void); */

int go_on = 1;			/* This variable controls the main loop. */

int main (int argc, char **argv)
{
  buffer_t *command_line;
  int i, j, aux;

  pipeline_t *pipeline;

  command_line = new_command_line ();
  /* test(); */
  
  pipeline = new_pipeline ();

  while (go_on)
    {
      printf ("%s ", PROMPT);
      fflush (stdout);
      aux = read_command_line (command_line);
      fatal (aux<0, NULL);

      /* Parse command line. */

      if (!parse_command_line (command_line, pipeline) || 1)
	{

	  
	  /* This is an example, of how to use pipeline_t. 
	     See foosh.h for detailed information. */

	  printf ("  Pipeline has %d command(s)\n", pipeline->ncommands);

	  for (i=0; pipeline->command[i][0]; i++)
	    {
	      printf ("  Command %d has %d argument(s): ", i, pipeline->narguments[i]);
	      for (j=0; pipeline->command[i][j]; j++)
		printf ("%s ", pipeline->command[i][j]);
	      printf ("\n");
	    }
	  

	  if ( RUN_FOREGROUND(pipeline))
	    printf ("  Run pipeline in foreground\n");
	  else
	    printf ("  Run pipeline in background\n");

	  
	  
	  if ( REDIRECT_STDIN(pipeline))
	    printf ("  Redirect input from %s\n", pipeline->file_in);
	  if ( REDIRECT_STDOUT(pipeline))
	    printf ("  Redirect output to  %s\n", pipeline->file_out);


	}
    }

  release_command_line (command_line);
  release_pipeline (pipeline);

  return EXIT_SUCCESS;
}
