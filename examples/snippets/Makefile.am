##   Makefile.am - Main Automake script for autohello
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

AM_CPPFLAGS = @CPP_FLAGS@ -Wno-unused-result -Werror
AM_CFLAGS =   @C_FLAGS@ 
AM_LDFLAGS =  @LD_FLAGS@

ACLOCAL_AMFLAGS = -I m4

noinst_bindir=/tmp/foo ## What is this???

noinst_bin_PROGRAMS = crash exec fork ioredir pipe2 pipe pipeline rpipeline signal2 signal loop toggle-io token siginfo setpgrp pthread semaphore

crash_SOURCES = crash.c
exec_SOURCES = exec.c
fork_SOURCES = fork.c
ioredir_SOURCES = ioredir.c
pipe2_SOURCES = pipe2.c
pipe_SOURCES = pipe.c
pipeline_SOURCES = pipeline.c
rpipeline_SOURCES = rpipeline.c
signal2_SOURCES = signal2.c
signal_SOURCES = signal.c
loop_SOURCES = loop.c
toggle_io_SOURCES = toggle-io.c
token_SOURCES = token.c
siginfo_SOURCES = siginfo.c
setpgrp_SOURCES = setpgrp.c
pthread_SOURCES = pthread.c
semaphore_SOURCES = semaphore.c

pthread_CC = @PTHREAD_CC@
pthread_LADD = @PTHREAD_LIBS@
pthread_CFLAGS=@PTHREAD_CFLAGS@

semaphore_CC = @PTHREAD_CC@
semaphore_LADD = @PTHREAD_LIBS@
semaphore_CFLAGS= @PTHREAD_CFLAGS@
