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


OBJECTS = crash.o exec.o fork.o ioredir.o pipe2.o pipe.o pipeline.o rpipeline.o signal2.o signal.o loop.o toggle-io.o token.o siginfo.o setpgrp.o pthread.o semaphore.o

INCLUDEPATH = . ../utils 
CPP_FLAGS = $(INCLUDEPATH:%=-I%) -Wall -Werror --std=c89 --pedantic-errors -D_POSIX_C_SOURCE=200112L 
C_FLAGS = -L.
LD_FLAGS =
CC = gcc

pthread semaphore : C_FLAGS="-pthread" 
pthread semaphore : LD_FLAGS ="-pthread"

BIN = $(OBJECTS:%.o=%)

all :$(BIN)

%.o : %.c
	$(CC) $(CPP_FLAGS) $(CPPFLAGS) $(C_FLAGS) $(CFLAGS) -c $<

$(BIN) : % : %.o
	gcc $(LD_FLAGS) $(LDFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS) $(BIN)
	rm -f *~ \#*



