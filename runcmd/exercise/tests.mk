
# Some tests

test:	all
	@rm -f nosuchfile *.log
	@echo "\nRunning tests...\n"
	@total=0;\
	for i in $(tests-bin); do echo;\
	./$$i; nerrors=$$?; total=$$(( $$total + $$nerrors)); done; \
	echo; \
	if test $$total -eq 0 ; then echo -n "Good! All tests ok!"; else echo -n "Found $$total error(s). Some tests failed."; fi;
	@echo; echo
