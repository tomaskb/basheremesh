##   Makefile.am - Automake script for example/snippets
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

AM_CPPFLAGS = @CPP_FLAGS@ -I$(top_srcdir)/lib -Wno-unused-result 
AM_CFLAGS =   @C_FLAGS@ 
AM_LDFLAGS =  @LD_FLAGS@

EXTRA_PROGRAMS = crash exec fork ioredir pipe2 pipe pipeline rpipeline signal2 signal loop toggle-io token siginfo setpgrp pthread semaphore crash

pthread_CC = @PTHREAD_CC@
pthread_LADD = @PTHREAD_LIBS@
pthread_CFLAGS=@PTHREAD_CFLAGS@

semaphore_CC = @PTHREAD_CC@
semaphore_LADD = @PTHREAD_LIBS@
semaphore_CFLAGS= @PTHREAD_CFLAGS@


all-local: $(EXTRA_PROGRAMS)

clean-local:
	rm -f $(EXTRA_PROGRAMS)
	rm -f @TEMPFILES@

