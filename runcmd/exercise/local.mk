# Project-specific rules

# Use this rule to test another lib implementatnion

testfoo:
	$(MAKE)
	rm -f $(tests-bin:%=%.o)
	$(MAKE) CPPFLAGS:="-I/tmp/foo/include" LDFLAGS:="-L/tmp/foo/lib -Wl,-rpath=/tmp/foo/lib" CFLAGS:="-g" test

