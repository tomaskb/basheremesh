# Run your tests
#

# Some tests for runcmd

tests-bin = test-runcmd

tests_setup:
	@rm -f nosuchfile *.log

test:	all tests_setup
	@echo "\nRunning tests...\n" 
	@total=0;\
	for i in $(tests-bin); do echo;\
	./$$i; nerrors=$$?; total=$$(( $$total + $$nerrors)); done; \
	echo; \
	if test $$total -eq 0 ; then echo -n "Good! All tests ok!"; else echo -n "Found $$total error(s). Some tests failed."; fi;
	@echo; echo

.PONY : tests_setup



