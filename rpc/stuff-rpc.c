/* stuff-rpc.c - Very Simple RPC Server, vr. 01

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

/* Instructions: modify this file to meet the project specification. */

#include <stdio.h>
#include <stdlib.h>
#include <stuff.h>
#include <debug.h>

/* See below. */
#define BUFFSIZE 512
#define CONFFIELDS 512
#define CONFIGFILE "rpc.config"
int init_connection (char *hosntame, int port);
void end_connection (int fd);
void read_config (void);
char *getconf (const char* );
char config[CONFFIELDS][BUFFSIZE][BUFFSIZE];
int confflag=0;

/* 
   Remote functions.
 */

/* Return the value of PI. */

float pi(void)
{
  read_config();
  fatal (1, "Not implemented");
  return 0;
}

/* Return n+1. */

int plusone (int n)
{
  read_config();
  fatal (1, "Not implemented");
  return 0;
}

/* Increment n. */

void increment (int *n)
{
  read_config();
  fatal (1, "Not implemented");
}

/* 
   RPC mechanism. 
*/

/* Connect to an RPC server at host 'hostname', port 'port' and
   return a socket file descriptor. On error, return -1. */

int init_connection (char *hosntame, int port)
{
  fatal (1, "Not implemented");
  return 0;
}

/* End the connection associated to the open file descriptor  fd.*/

void end_connection (int fd)
{
  fatal (1, "Not implemented");

}

/* Read configuration file (once). */

void read_config (void)
{
  FILE *file;
  char name[BUFFSIZE], value[BUFFSIZE];
  int i;

  if (confflag)
    return;
  else
    confflag=1;

  i=0;

  file = fopen (CONFIGFILE,"r");
  sysfatal (!file);
  while ((i<CONFFIELDS) && (fscanf (file, "%s : %s", name, value) != EOF))
    {
      strncpy(config[i][0], name,  BUFFSIZE-1);
      strncpy(config[i][1], value, BUFFSIZE-1);
      i++;
    }
  
}

/* Get value of config field 'name'. */

char *getconf (const char* name)
{
  int i;
  i=0;
  while ( (i<CONFFIELDS) && (strcmp(config[i][0],name)))
    i++;
  if (i<CONFFIELDS)
    return config[i][1];
  else
    return NULL;
}

