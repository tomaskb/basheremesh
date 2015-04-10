# Makefile - For the example of static and shared lib 
#
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

# Flags to gcc

CC = gcc
CPP_FLAGS = -I. -Wall -Werror --std=c89 --pedantic-errors -D_POSIX_C_SOURCE=200112L 
C_FLAGS = -Wall
LD_FLAGS = -L.

# We're building two versions of the same executables. Both are
# linked to libfoo: one linked to the static libfoo.a and the other
# linked to the shared (dynamic) libfoo.so

binary = main-static main-shared

# Make all

all: $(binary)

#
# STATIC VERSION
#

# A static lib is just an archive (concatenation) containing all the object
# plus an index of object-files.

libfoobar.a: foo.o bar.o
	ar rcs $@ $^

# The pattern rule to build objects from sources 

%.o : %.c
	$(CC) $(CPP_FLAGS) $(CPPFLAGS) $(C_FLAGS) $(CFLAGS) -c $<

# To compile the statically-linked executable all that we would
# need is a regular compilation like
# $(CC) $(LD_FLAGS) $(LDFLAGS) main.o -lfoo -o $@
# The gcc -lfoo will link the executable to libfoo.a
# The problem is that, if the dynamic version libfoo.so alo exists,
# it will be used by default. Thus, we have to explicitly tell gcc
# to use the statif version.  This might be done with gcc -static;
# however, that would cause gcc to use the static version of libc
# as well.  Instead, we use linker flags -Wl,-Bstatic to toggle the
# linker to the static mode when it comes to link -lfoo; and toggle
# the linker back to the shared mode with -Wl,-Bdynamic, so that
# the shared libc is used.

main-static: main.o libfoobar.a
	$(CC) $(LD_FLAGS) $(LDFLAGS) main.o -Wl,-Bstatic -lfoobar -Wl,-Bdynamic -o $@


#
# SHARED VERSION
#

# A shared lib is created using gcc -shared from object files
# compliped with position independent code.

libfoobar.so: foo-pic.o bar-pic.o
	$(CC) $(CPP_FLAGS) $(CPPFLAGS) $(C_FLAGS) $(CFLAGS) -shared $^ -o $@

# Pattern rule to creatte position-independent object files from sources
# This makes difference in m68k, PowerPC and SPARC.

%-pic.o: %.c
	$(CC) $(CPP_FLAGS) $(CPPFLAGS) $(C_FLAGS) $(CFLAGS) -fPIC -c $< -o $@

# This will create an executable linked to the dynamic version of libfoo
# if it exists.  In order to execute it, if libfoo.so is not in the
# usual library path, set the environment variable LD_LIBRARY_PATH, like
# this on Bash: export LD_LIBRARY_PATH=.

main-shared: main.o libfoobar.so
	$(CC) $(LD_FLAGS) $(LDFLAGS) main.o -lfoobar -o $@

# A gcc trick to include automatic header dependencies

makefiles = main.d foo.d bar.d
%.d: %.c
	$(CC) -MM -MT '$(<:.c=.o) $@' $(CPP_FLAGS) $(CPPFLAGS) $< >$@
include $(makefiles)

# Clean up everything

.PHONY clean:
	rm -f  *~ *.o *.so \#*  *.d
	rm -f libfoobar.a libfoobar.so main-static main-shared



