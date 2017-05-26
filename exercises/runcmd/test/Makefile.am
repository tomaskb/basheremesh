##   Makefile.am - Automake script for exercises/runcmd/test.
##
##   Copyright (c) 2014, Francisco Jose Monaco  <moanco@icmc.usp.br>
##
##   This file is part of POSIXeg.
##
##   POSIXeg is free software: you can redistribute it and/or modify
##   it under the terms of the GNU General Public License as published by
##   the Free Software Foundation, either version 3 of the License, or
##   (at your option) any later version.
##
##   This program is distributed in the hope that it will be useful,
##   but WITHOUT ANY WARRANTY; without even the implied warranty of
##   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
##   GNU General Public License for more details.
##
##   You should have received a copy of the GNU General Public License
##   along with this program.  If not, see <http://www.gnu.org/licenses/>.

#AM_CPPFLAGS = @CPP_FLAGS@ -I$(srcdir)/../lib -I$(builddir)/../lib -I$(top_srcdir)/lib -I$(top_builddir)/lib -Wno-unused-result

ALTCPPFLAGS = -I$(ALTPREFIX)/include
ALTLDFLAGS = -L$(ALTPREFIX)/lib -Wl,-rpath=$(ALTPREFIX)/lib

AM_CPPFLAGS = @CPP_FLAGS@ $(ALTCPPFLAGS) -I../lib  -I$(top_srcdir)/lib -I$(top_builddir)/lib -Wno-unused-result  
AM_CFLAGS =   @C_FLAGS@ 
AM_LDFLAGS =  @LD_FLAGS@ $(ALTLDFLAGS) -L../lib 

# make CPPFLAGS="-I/tmp/foo/include" LDFLAGS="-L/tmp/foo/lib -Wl,-rpath=/tmp/foo/lib"

bindir = $(abs_srcdir)/build
bin_PROGRAMS = test-001 test-002 test-003 test-004 t1 t2 

EXTRA_DIST = t.h testutils.h 

test_001_SOURCES = test-001.c testutils.c 
test_002_SOURCES = test-002.c testutils.c
test_003_SOURCES = test-003.c testutils.c
test_004_SOURCES = test-004.c testutils.c


LDADD = $(top_builddir)/lib/libposixeg.la -lruncmd

test_002_CC = @PTHREAD_CC@
test_002_LDADD = $(LDADD) @PTHREAD_LIBS@
test_002_CFLAGS= $(AM_CFLAGS) @PTHREAD_CFLAGS@

all-local: $(EXTRA_PROGRAMS)

clean-local:
	rm -f $(EXTRA_PROGRAMS)
	rm -f @TEMPFILES@

mytests = test-001 test-002 test-003 test-004


test: $(bin_PROGRAMS)
	$(MAKE) install
	@echo "\n----------------------------------------------------------------------"
	@echo "\nRunning tests\n"
	@total=0;\
	for i in $(mytests); do echo;\
	./build/$$i; nerrors=$$?; total=$$(( $$total + $$nerrors)); done; \
	echo; \
	if test $$total -eq 0 ; then echo -n "Good! All tests ok!"; else echo -n "Found $$total error(s). Some tests failed."; fi;
	@echo; echo



