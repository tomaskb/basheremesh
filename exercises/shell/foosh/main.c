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
#include <basheremesh/lib/posixeg/tparse.h>
#include <basheremesh/lib/posixeg/tparse.h>

#define PROMPT "@:"

/* void test(void); */

int go_on = 1;			/* This variable controls the main loop. */

int main (int argc, char **argv)
{
  buffer_t *command_line;
  int i, j, aux;

  pipeline_t *pipeline;

  command_line = new_command_line (); 
  
  pipeline = new_pipeline ();

  /* This is the main loop. */

  char line[BUFFER];

    while(1) {
        printf("$ ");
        if(!fgets(line, BUFFER, stdin)) break;
        char *p = strchr(line, '\n');
        if (p) *p = 0;
        if(strcmp(line, "exit")==0) break;
        char *args[] = {line, (char*)0};
        int pid= fork();              //fork child
        if(pid==0) {               //Child
            execvp(line, args);
            perror("exec");
            exit(1);
        } else {                    //Parent
            wait(NULL);
        }
    }
	
	
  release_command_line (command_line);
  release_pipeline (pipeline);

  return EXIT_SUCCESS;
}
