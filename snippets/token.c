/* token.c - Exemple of the use of strtok to parse command line. 

   Copyright (c) 2015, Monaco F. J. <moanco@icmc.usp.br>

   This file is part of POSIX.

   POSIX is free software: you can redistribute it and/or modify
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
#include <string.h>
#include <stdlib.h>

int main (int argc, char **argv)
{
  char buffer[1024], *p;

  /* This is an example of a line we ant to parse. */
  strcpy (buffer, "Hello Token World");

  printf ("Buffer is: %s\n", buffer);

  /* The function strtok process the string in 'buffer' and finds the first 
     ocurrency of any of the characters present in the string 'delimiters'
     
     p = strtok (char *buffer, char *deliminters)

     The function puts a string-end mark ('\0') where it found the delimiter
     and returns a pointer to the bining of the buffer.
*/

  /* Finds the first white space in buffer. */
  p = strtok (buffer, " ");

  /* Now, go on searching for the next delimiters. 

     p = strtok (NULL, char *delimiters)

     The function "remembers" the place where it found the delimiter.
     If the furst argument is NULL, the function starts searching
     from this position instead of the start of buffer. Therefore
     it will find the first delimiter starting from where it ended
     the last time, and will return a pointer to the first 
     non-delimiter after this point (that it, the next token).
*/

  while (p != NULL)
    {
      printf ("Token: %s\n", p);
      p = strtok (NULL, " ");	/* Find the next token. */
    }

  /* Notice that strtok destroys 'buffer' by adding '\0' to every
     ocurrency of a delimiter.*/

  printf ("Now buffer is: %s\n", buffer);

  /* See 'man strtok' or the libc manual for furter information. */

  return EXIT_SUCCESS;
}
