# Makefile

# Copyright (c) 2015, Monaco F. J. <moanco@icmc.usp.br>
#
# This file is part of POSIXeg.
#
# POSIXeg is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.


OBJECTS = crash.o eg-exec.o eg-fork.o eg-io-redirect.o eg-pipe2.o eg-pipe.o eg-pipeline.o eg-signal-better.o eg-signal.o loop.o toggle-output.o token.o

CPP_FLAGS = -I. -Wall -Werror --std=c89 --pedantic-errors -D_POSIX_C_SOURCE=200112L 
C_FLAGS = -L.
LD_FLAGS =
CC = gcc

BIN = $(OBJECTS:%.o=%)

all :$(BIN)

%.o : %.c
	$(CC) $(CPP_FLAGS) $(CPPFLAGS) $(C_FLAGS) $(CFLAGS) -c $<

$(BIN) : % : %.o
	gcc $(LD_FLAGS) $(LDFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS) $(BIN)
	rm -f *~ \#*



