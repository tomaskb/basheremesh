/*  rpc.h - 
    
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

#ifndef POSIXEG_RPC_H
#define POSIXEG_RPC_H

#define BUFFSIZE 512		/* Static buffer for simplicity. */
#define CONFFIELDS 512		/* Max configuration tokens. */
#define CONFIGFILE "rpc.config"	/* Configuration file. */

/*  Connect to server (hostname, port), call function 'string' and receive
    the reply in 'buffer'*/

void call_remote (const char *hostname, int port, char *string, char *buffer);

/* Read configuration file. */
void read_config (void);

/* Get a configuration value for a given field.  */
char *getconf (const char* field);

#endif   /*POSIXEG_RPC_H */
