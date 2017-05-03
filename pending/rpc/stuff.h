/* stuff.h- Very Simple RPC Server, vr. 01

   Copyright 2014  Monaco F. J.   <monaco@icmc.usp.br>

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

#ifndef STUFF_H
#define STUFF_H

float pi(void);

float phi (void);

int plusone (int );

void increment (int *);

#define LOGFILE "log.txt"
#define LOGBUFFSIZE 1024

int read_log (void);
int write_log (void);

typedef char * buffer_t;

buffer_t new_buffer (int);
void set_buffer (buffer_t , const char *, int);
void get_buffer (char *, buffer_t, int);
void free_buffer (buffer_t);

#endif	/* STUFF_H */
