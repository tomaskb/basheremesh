/* foo.h - Header of our example-library.

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

#ifndef FOO_H
#define FOO_H

#define NORMAL_TERMINATION    0
#define ABNORMAL_TERMINATION  1

#define BLOCK 0
#define NONBLOCK 1


/* This struct is passed to function runcommand. */

typedef struct 
{
  char **args;			/* A command vector as it is passed to exec. */
  int exit_status;		/* Exit status code returned by the program. */
  int termination;		/* Process terminated normally or abnormally. */
  int *io;			/* io[i]: standard input, ouput and error. */
  int mode;			/* Either BLOCK or NONBLOCK. */
} command_t;


/* Run a command in a subprocess. */

int runcommand (command_t *command);

#define CMD_MAX_ARGS   1024
#define CMD_DELIMITERS " \n\t\r"
#define CMD_BACKGROUND '&'
#define NORMAL        (1 <<  8)	/* 256 */
#define EXECOK        (1 <<  9)	/* 1024 */
#define BACKGROUND    (1 << 10)	/* 2048 */
#define EXITSTATUS    (0xFF)	/* 255 */


#define IS_NORMAL(result)        ((*result & NORMAL) && 1)
#define IS_NONBLOCK(result)      ((*result & BACKGROUND) && 1)
#define IS_EXECOK(result)        ((*result & EXECOK) && 1)
#define EXITVALUE(result)        ( *result & EXITSTATUS)

int runcmd (char *command, int *result, int *io);

/* Hanlder for SIGCHLD in NONBLOCK mode. */

extern void (*runcmd_onexit)(void);

#endif	/* FOO_H */
