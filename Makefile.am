##   Makefile.am - Main Automake script.
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

directories = examples tools extras exercises/shell/foosh 

SUBDIRS = lib 
DIST_SUBDIRS = $(SUBDIRS) $(directories) 
ACLOCAL_AMFLAGS = -I m4


force-all:
	for i in $(directories) ; do $(MAKE) -C $$i; done

clean-local:
	for i in $(directories) ; do \
	   if test -f $$i/Makefile ; then $(MAKE) -C $$i clean; fi\
        done
	rm -f $(TEMPFILES)

install-exec-local:
	for i in $(directories) ; do $(MAKE) -C $$i install; done

uninstall-local:
	for i in $(directories) ; do $(MAKE) -C $$i uninstall; done



