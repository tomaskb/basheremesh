/*  memory-rpc.c - 
    
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

#include <stdlib.h>
#include <stuff.h>

/* These functions correspond to the local implementation and were
   copied from memory. c. Please, modify them to implement the
   RPC version. */

buffer_t new_buffer (int size)
{
  void *p;
  
  p = malloc (size);

  return p;
}

void set_buffer (buffer_t target, const char *source, int length)
{
  int i;

  for (i=0; i<length; i++)
    target[i] = source[i];
  
}

void get_buffer (char *target, buffer_t source, int length)
{
  int i;

  for (i=0; i<length; i++)
    target[i] = source[i];
  
}

void free_buffer (buffer_t buffer)
{
  free (buffer);
}
