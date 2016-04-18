# These files are generated in the development enviroment and 
# distributed along with other source files.

# Rationales. 
#
# When biding this subproject (runcmd) we want to reuse some header
# files of the main project (posixeg) . We, however, do not want to add
# the source header path to the preprocessor because the subproject's
# makedist rule shall not reach beyond the subproject's directory. 
# Instead, we have a rule to copy the reused headers from their original
# location in the main project's tree to the current building directory
# every time the main project's header is modified. So far so good.
# The problem is that the subproject's Makefile is packed into makedist's
# outcome. When the tarball is decompressed in the user's filesystem,
# the main project's path may be different or non existent.  The trick
# is then to add the generated headers to the makedist's outcome and 
# remove the rule from the distributed Makefile. To that end, we have
# this includable makefile in the subprojects's directory. It is not
# added to the makedist's tarball, though; rather, the main Makefile
# has a rule to recreate it in the user's installation. Nevertheless,
# this rule outputs an empty makefile. And the problem is solved.


SRCDIR = ../..

debug.h : $(SRCDIR)/utils/debug.h 
	@echo "copying $@ from $<"
	cp $< .
