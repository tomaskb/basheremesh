##   Makefile.am - Automake script for examples.
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

SUBDIRS = snippets
EXTRA_DIST = library/main.c library/foo.c library/bar.c library/foobar.h library/Makefile library/README

EXTRA_DIST += Makefile-eg/README Makefile-eg/main.c Makefile-eg/circle.c Makefile-eg/circle.h Makefile-eg/rectangle.c Makefile-eg/rectangle.h Makefile-eg/square.c Makefile-eg/square.h Makefile-eg/deps/deps.fig  Makefile-eg/deps/deps.pdf Makefile-eg/Makefile-00 Makefile-eg/Makefile-01 Makefile-eg/Makefile-02 Makefile-eg/Makefile-03 Makefile-eg/Makefile-04 Makefile-eg/Makefile-05 Makefile-eg/Makefile-06 Makefile-eg/Makefile-07 Makefile-eg/Makefile-08 Makefile-eg/Makefile-09 


clean-local:
	$(MAKE) $(AM_MAKEFLAGS) -C $(srcdir)/library clean


