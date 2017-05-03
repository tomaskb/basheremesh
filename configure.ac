dnl    configure.ac - Autoconf script 
dnl    
dnl    Copyright 2015  Monaco F. J.   <monaco@icmc.usp.br>
dnl
dnl    This file is part of POSIXeg. 
dnl
dnl    POSIXeg is free software: you can redistribute it and/or modify
dnl    it under the terms of the GNU General Public License as published by
dnl    the Free Software Foundation, either version 3 of the License, or
dnl    (at your option) any later version.
dnl
dnl    POSIXeg is distributed in the hope that it will be useful,
dnl    but WITHOUT ANY WARRANTY; without even the implied warranty of
dnl    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
dnl    GNU General Public License for more details.
dnl
dnl    You should have received a copy of the GNU General Public License
dnl    along with .  If not, see <http://www.gnu.org/licenses/>.
dnl

AC_INIT([POSIXeg], [0.1.0], [monaco@icmc.usp.br])   dnl Init Autoconf
AC_PREREQ([2.65])                              dnl Required autoconf version    
AC_CONFIG_AUX_DIR([build-aux])                 dnl Where to write auxiliary files                                                                              
AC_CONFIG_MACRO_DIR([m4])                      dnl m4 files here       
AC_CONFIG_HEADERS([config.h])                  dnl Generate config.h   

AM_INIT_AUTOMAKE([-Wall -Werror 1.14.1 subdir-objects])	dnl Init Automake options

AM_PROG_AR                      dnl Archiver for static lib                     
LT_INIT                         dnl Libtool support in 'configure'  

AC_PROG_CC 		        dnl Defines CC

dnl Define variables to be used by Automake

AC_SUBST([CPP_FLAGS],"-ansi -D_POSIX_C_SOURCE=200809L -Wall -Werror --pedantic") dnl Define flags
AC_SUBST([C_FLAGS])
AC_SUBST([LD_FLAGS])
AC_SUBST([TEMPFILES],[*~ `@%:@*`])

dnl Canocial check for POSIX threads.

AX_PTHREAD([
AC_DEFINE(HAVE_PTHREAD,1,[Define to 1 if POSIX threads libraries and headers are found.]) ], 
AC_MSG_WARN([POSIX threads support not detected.]))

dnl Output files

AC_CONFIG_FILES([
Makefile
lib/Makefile
examples/Makefile
examples/snippets/Makefile
exercises/Makefile
exercises/shell/Makefile
exercises/shell/foosh/Makefile
exercises/shell/tests/Makefile
exercises/runcmd/Makefile
exercises/runcmd/lib/Makefile
exercises/runcmd/test/Makefile
extras/Makefile
tools/Makefile
doc/Makefile])	

AC_OUTPUT			dnl Do it

