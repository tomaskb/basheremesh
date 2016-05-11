/* t1.h - Auxiliary program to test runcmd.

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

#ifndef T1_H
#define T1_H

/* Arguments. */

# define T1_SEGFAULT  15	  /* Cause program to segfault. */
# define T1_SOMEVALUE 11	  /* Reserved to test return atoi(argv[1]). */
# define T1_MAKEIO    12	  /* Reads from stdin and writes to stdout. */

/* Exit status. */

# define T1_NOARG     10	/* If no argument is given, return this value. */

#endif	/* T1_H */
