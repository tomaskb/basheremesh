/*  client-05.c - Allocate memory.
    
    Copyright 2015  Francisco Jose Monaco   <moanco@icmc.usp.br>

    This file is part of POSIXeg. 

    POSIXeg is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    POSIXeg is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with .  If not, see <http://www.gnu.org/licenses/>. 

*/

#include <stdio.h>
#include <stdio.h>

#include <debug.h>
#include <stuff.h>

#define LENGTH 10

int main (int argc, char **argv)
{
  buffer_t buffer;
  char *p;

  buffer = new_buffer (LENGTH);
  fatal (!buffer, "Can't allocate memory");

  set_buffer (buffer, "abcd", 5);

  p = malloc (LENGTH);
  get_buffer (p, buffer, 5);

  printf ("Buffer: %s\n", p);

  free_buffer (buffer);


  return EXIT_SUCCESS;
}
