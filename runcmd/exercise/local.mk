# Project-specific rules

# Use this rule to boostrap a new exercise.

SKEL=skeleton

$(SKEL:%=%) : $(SKEL:%=%).tgz

#skeleton.tgz : $(proj_src) $(proj_headers) $(EXTRA_DIST) $(gendist_files)
skeleton.tgz : runcmd.c Makefile runcmd.h
	rm -rf $(SKEL:%=%)
	mkdir $(SKEL:%=%)
	cp $^ $(SKEL:%=%)
	tar zcvf $(SKEL:%=%).tgz $(SKEL:%=%)

other_tests = test-003

test-extra:	all tests_setup
	@echo "\n----------------------------------------------------------------------"
	@echo "\nRunning extra tests\n"
	@total=0;\
	for i in $(other_tests); do echo;\
	./$$i; nerrors=$$?; total=$$(( $$total + $$nerrors)); done; \
	echo; \
	if test $$total -eq 0 ; then echo -n "Good! All tests ok!"; else echo -n "Found $$total error(s). Some tests failed."; fi;
	@echo; echo
