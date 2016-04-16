# Makefile - Simple Makefile to build a library.
#
# Copyright 2014  Monaco F. J.  <monaco@icmc.usp.br>
#
# This file is part of POSIXeg. 
#
#  POSIXeg is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 3 of the License, or
#  (at your option) any later version.
#
#  SICSE is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with .  If not, see <http://www.gnu.org/licenses/>. 


# Directions: 
#
# make		    builds everything
# make clean	    clean up the mess
# make dist	    pack files to distribute
# make distclean    restore to original state
# make install      install the libraries
# make uninstall    uninstall the libraries
# make test         perform all runtime tests


#
# Do not touch bellow this line.
#

# Give the project a name
PROJECTNAME = runcmd

# Sources needed to build the library
libsources = runcmd.c 

# Headers to be distributed
libheaders = foo.h

# Where do you want to install the lib
PREFIX=.

# Name your tests (baz is made from baz.c with the library)

tests-bin = test-runcmd 

# Auxiliary programs (baz is made from baz.c only)

aux-bin = segfault io delay

# Building tools

INCLUDEPATH = . ../../utils 

CC = gcc
CPP_FLAGS = $(INCLUDEPATH:%=-I%) -Wall -Werror -std=c89 --pedantic-errors -D_POSIX_C_SOURCE=200112L 
C_FLAGS = 
LD_FLAGS = -L. 
MAKE = make
SHELL = /bin/sh 

#
# Mostly automatic from here on
#

libfile = lib$(PROJECTNAME).a

all: $(libfile) $(tests-bin) $(aux-bin)

libobjects = $(libsources:.c=.o)

$(libfile): $(libobjects)
	ar rcs $@ $^

%.o : %.c 
	$(CC) $(CPP_FLAGS) $(CPPFLAGS) $(C_FLAGS) $(CFLAGS) -c  $<

makefiles = $(libobjects:%.o=%.d) $(tests-bin:%=%.d) $(aux-bin:%=%.d)
%.d : %.c
	$(CC) $(CPP_FLAGS) $(CPPFLAGS) -MM -MT '$(<:%.c=%.o) $@' $< > $@

ifeq (,$(filter clean distclean,$(MAKECMDGOALS)))
include $(makefiles)
endif

tests-source = $(tests-bin:%=%.c)

aux-source = $(aux-bin:%=%.c)

dist: $(libsources) *.h Makefile $(tests-source) $(aux-source)
	rm -rf $(PROJECTNAME)
	mkdir $(PROJECTNAME)
	cp $^ $(PROJECTNAME)
	tar zcvf $(PROJECTNAME).tgz $(PROJECTNAME)
	rm -rf $(PROJECTNAME)


clean: 
	rm -f *.o $(makefiles) $(libfile) *~ $(tests-bin) $(aux-bin) *\# \.\#* 
	rm -f *.txt
	rm -rf $(PROJECTNAME) $(NUSP)

distclean: clean
	rm -f $(PROJECTNAME).tgz

install : $(libfile) $(libheaders)
	install -d $(PREFIX)/lib
	install -d $(PREFIX)/include
	cp $(libfile) $(PREFIX)/lib/
	cp $(libheaders) $(PREFIX)/include/

uninstall: 
	rm -f $(PREFIX)/lib/$(libfile)
	rm -f $(PREFIX)/include/$(libheaders)


$(tests-bin) : % : %.o $(libfile) $(libheaders)
	$(CC) $(LD_FLAGS) $(LDFLAGS) $^ -o $@	 -l$(PROJECTNAME)

$(aux-bin) : % : %.o
	$(CC) $(LD_FLAGS) $(LDFLAGS) $^ -o $@	 


# Test

test:	all
	@rm -f nosuchfile *.log
	@echo "\nRunning tests...\n"
	@total=0;\
	for i in $(tests-bin); do echo;\
	./$$i; nerrors=$$?; total=$$(( $$total + $$nerrors)); done; \
	echo; \
	if test $$total -eq 0 ; then echo -n "Good! All tests ok!"; else echo -n "Found $$total error(s). Some tests failed."; fi;
	@echo; echo

.PHONY = clean 
clean : INCLUDE_D=NO

