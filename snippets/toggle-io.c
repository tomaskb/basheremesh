/* toogle-io.c - Redirects the output to a file and then bach to terminal. 

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
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main (int arch, char **argv)
{
  int status;
  int fd, fd2;

  /* First we duplicate the standard output: fd=dup(1) creates
     a new file descript  which points to the same file pointed
     by file descriptor 1. For example, if descript 1 points to
     /dev/tty, then now we have a new descriptor 3 pointing to 
     the same device. */

  fd = dup (1);

  printf ("fd=%d\n", fd);	/* Just to show that fd==3. */
  fflush(stdout);

  /* Now we close the standard output file descriptor. Descriptor
     1 is then empty.*/

  close (1);

  /* Next step is to open the output file. Since the first availble
     file descriptor is 1, this will be our new standard output. */

  fd2 = open ("output.txt", O_CREAT | O_TRUNC | O_RDWR, S_IRUSR | S_IWUSR);
  if (fd2<0)
    {perror("ops"); exit(1);}

  /* All printf calls will go to the output file. */

  status = printf ("To file\n");
  fprintf (stderr, "status: %d (%s)\n", status, strerror(errno));
  fflush(stdout);
  
  /* Now we want to restore the original standard output. Again we close
     descriptor 1. */

  close (fd2);

  /* Then we dup fd (which is 3), so that now once more we have to descriptors
     pointing to the same device (e.g. /dev/tty). The copy will be associated
     with file descriptor 1 (the lowest available).*/

  dup (fd);

  /* Finale we close descriptor 3, the backup of descriptor 1. */

  close (fd);

  /* And voila, we have the original standard output. */

  printf ("To console\n");

  /* Alternatively, you may think of using function dup2() instead. */

  return 0;
}
