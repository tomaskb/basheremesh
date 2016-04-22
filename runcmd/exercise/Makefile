# Makefile - Build runcmd project.
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


# Directions: 
#
# make		    builds everything
# make clean	    clean up the mess
# make dist	    pack files to distribute
# make distcheck    make dist and check package
# make install      install the libraries
# make uninstall    uninstall the libraries
# make test         perform all runtime tests


#
# COSTOMIZE FOR YOUR PROJECT
#

# Give your project a name, e.g.
# PROJECT = FooBar

PROJECT = runcmd

# Name your project's binaires, eg.
# bin = foo bar
bin = test-runcmd

# For each item in $(bin), name the objects needed to build it, e.g.
# foo_obj = main_foo.o 
# bar_obj = main_bar.o 
test-runcmd_obj = test-runcmd.o

# For each item in $(bin), name the project's libraries to which it shall be linked, e.g.
# foo_lib = libfoobar
# bar_lib = libfoobar libm
test-runcmd_lib = libruncmd

# For each item in $(bin), name the other libraries to which it shall be linked, e.g.
# foo_lib_other = libfoobar
# bar_lib_other = libfoobar libm


# Name your project's libraries (to be installed), e.g.
# lib = libfoobar
lib = libruncmd

# For each item in $(lib), name the objects needed to build it, e.g.
# libfoobar_obj = foo.o bar.o
libruncmd_obj = runcmd.o

# For each item in $(lib), name the headers your project installs, e.g.
#libfoobar_h = foos.h
libruncmd_h = runcmd.h

# Name your project's auxuliary binaries (not to be installed), e.g.
# noinst_bin = example
noinst_bin = delay io segfault

# For each item in $(noinst_bin), name the objects needed to build it, e.g.
# example_obj = example.o 
delay_obj = delay.o
io_obj = io.o
segfault_obj = segfault.o


# For each item in $(noinst_bin), name the libraries to which it's to be linked, e.g.
# example_lib = libfoobar


# Extra files to go in the distribution (add as needed)

EXTRA_DIST =

# Generated, distributed headers (list the 
# (Note: rf gcc -MM -MG treated missing local headers as it does for 
# gcc -M -MG, we might go without this artifice)

# List the automatically generated, distributed source files of any kind.
# These files are generated in the development environment but should
# be already available in the building enviroment. E.g. config scripts.

gendist_files = debug.h # -MG in gcc -MM -MG does not work as for gcc -M -MG

# Installation prefix

PREFIX=./local

# Customize the building environemnt (modify as desired)

CC = gcc
CPP_FLAGS = -I. -Wall --ansi --pedantic-errors -D_POSIX_C_SOURCE=200112L 
C_FLAGS = 
LD_FLAGS = -L.
MAKE = make
AR = ar

# Housekeeping (name temporary files to clean)
# EXTRA_GARBAGE = *~
EXTRA_GARBAGE = *~ \#*

#
# YOU WON'T PROBABLY NEED TO MODIFY BELLOW THIS LINE
#
# Automatic from here on


#
# Handy variables
#

lib_static = $(lib:%=%.a)              # For building
lib_shared = $(lib:%=%.so)             # For building

# Used for installation
lib_all = $(lib_static) $(lib_shared)  # For installing

inst_headers = $(foreach i, $(lib:%=%_h), $($i))  # For installing

proj_src += $(foreach i, $(lib:%=%_obj), $($i:%.o=%.c))  # For distribution
proj_src += $(foreach i, $(bin:%=%_obj), $($i:%.o=%.c))
proj_src += $(foreach i, $(noinst_bin:%=%_obj), $($i:%.o=%.c))

proj_dep = $(proj_src:%.c=%.d)  # For building

proj_headers += $(filter %.h, $(shell $(CC) $(CPP_FLAGS) $(CPPFLAGS) -MM -MG -MT " " $(proj_src)) )
proj_headers += $(inst_headers) # For distribution

EXTRA_DIST += Makefile tests.mk local.mk

#
# Rules
#

# Build everything


all static : $(gendist_files) $(lib_all) $(bin) $(noinst_bin) 

.SECONDEXPANSION:

# Pattern rules for building libraries

$(lib_static) : %.a : $$($$*_obj)
	$(AR) rcs $@ $^

$(lib_shared) : %.so : $$($$*_obj:.o=-pic.o)
	$(CC) -shared $(LD_FLAGS) $(LDFLAGS) $^ -o $@


# Pattern rules for building binaires (uses secondary expansion).
# By default, both static and shared libraries are built and installed. 
# The binary is dynalically linked. If the executables are to be linked 
# against the static libraries, the target'static' produces this result. 
# This does not prevent the building and installation of the shared 
# libraries, anyway.

ifneq (,$(filter static, $(MAKECMDGOALS))) 
#
# Statically linked
#

$(bin) : % : $$($$*_obj)  | $$(foreach i, $$($$*_lib), $$i.a)
	$(CC) $(LD_FLAGS) $(LDFLAGS)  $^ -Wl,-Bstatic $(|:lib%.a=-l%) -Wl,-Bdynamic $(patsubst lib%, -l%, $($*_lib_other))  -o $(@:%=.%)
	echo "#!/bin/sh\n./$(@:%=.%)" > $@
	chmod u+x $@

$(noinst_bin): % : $$($$*_obj)  | $$(foreach i, $$($$*_lib), $$i.a)
	$(CC) $(LD_FLAGS) $(LDFLAGS)  $^ -Wl,-Bstatic $(|:lib%.a=-l%) -Wl,-Bdynamic $(patsubst lib%, -l%, $($*_lib_other))  -o $@
	chmod u+x $@

else
#
# Dynamically linked
#

$(bin) : % : $$($$*_obj)  | $$(foreach i, $$($$*_lib), $$i.so)
	if ! -d $(PREFIX) ; then install -d $(PREFIX) ; fi 
	$(CC) $(LD_FLAGS) $(LDFLAGS) -Wl,-rpath=$(realpath $(PREFIX))/lib $^ $(|:lib%.so=-l%) $(patsubst lib%, -l%, $($*_lib_other))  -o $(@:%=.%)
	echo "#!/bin/sh\nLD_LIBRARY_PATH=. ./$(@:%=.%)" > $@
	chmod u+x $@

$(noinst_bin): % : $$($$*_obj)  | $$(foreach i, $$($$*_lib), $$i.so)
	if ! -d $(PREFIX) ; then install -d $(PREFIX) ; fi 
	$(CC) $(LD_FLAGS) $(LDFLAGS) -Wl,-rpath=. $^ $(|:lib%.so=-l%) $(patsubst lib%, -l%, $($*_lib_other))  -o $@
	chmod u+x $@


endif

#
# New scheme
#


# Pattern rules sufix-rules fror object-to-source dependency

%.o : %.c
	$(CC) $(CPP_FLAGS) $(CPPFLAGS) $(C_FLAGS) $(CFLAGS) -c  $< -o $@

%-pic.o : %.c
	$(CC) $(CPP_FLAGS) $(CPPFLAGS) $(C_FLAGS) $(CFLAGS) -c  -fPIC $< -o $@

# Atuomatically calculate header dependences

%.d : %.c
	$(CC) $(CPP_FLAGS) $(CPPFLAGS) -MM -MG -MT '$(<:.c=.o) $@' $< > $@

%-pic.d : %.c
	$(CC) $(CPP_FLAGS) $(CPPFLAGS) -MM -MG -MT '$(<:.c=-pic.o) $@' $< > $@

ifeq (,$(filter clean uninstall, $(MAKECMDGOALS))) # Don't do it if not needed
-include $(proj_dep)
endif


.PHONY: clean dist distcheck install uninstall

clean: 
	rm -f *.o *.d $(lib_static) $(lib_shared) $(bin) $(noinst_bin) $(bin:%=.%) $(noinst_bin:%=.%)
	rm -f $(EXTRA_GARBAGE) 
	rm -rf $(PROJECT) $(PROJECT).tgz


# Distribution

dist: $(PROJECT).tgz

$(PROJECT).tgz : $(proj_src) $(proj_headers) $(EXTRA_DIST) $(gendist_files)
	rm -rf $(PROJECT)
	mkdir $(PROJECT)
	cp $^ $(PROJECT)
	tar zcvf $(PROJECT).tgz $(PROJECT)

distcheck: dist
	if $(MAKE) -C $(PROJECT) ; then echo "\n$(PROJECT).tgz ready for distribution"; \
	else echo "\nSomething wrong with $(PROJECT).tgz"; fi; echo 

# Install, uninstall

install: INSTALL=yes
install : $(lib_all) $(bin) $(inst_headers) 
	install -d $(PREFIX)/lib
	install -d $(PREFIX)/include
	install -d $(PREFIX)/bin
	cp $(lib_all) $(PREFIX)/lib/
	cp $(inst_headers) $(PREFIX)/include/
	for i in $(bin:%=.%); do if test -f $$i ; then cp $${i#.} $(PREFIX)/bin; fi; done

uninstall: 
	for i in $(lib_all) ; do rm -f $(PREFIX)/lib/$$i; done
	for i in $(inst_headers) ; do rm  -f $(PREFIX)/include/$$i; done
	for i in $(bin) ; do rm -f $(PREFIX)/bin/$${i#.}; done


# Submakefiles

-include gendist.mk # Distributed produced files (see gendist.mk)

-include tests.mk  # Run tests, if any

-include local.mk  # Project-specific rules, if any.

gendist.mk tests.mk local.mk : 
	touch $@
