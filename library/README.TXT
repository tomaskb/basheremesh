
Examples of how to create both static and shared libraries.

foobar.h    declares foo() and bar()
foo.c	    implements foo()
bar.c	    implements bar()
main.c	    the example program

Run 'make' to build

libfoobar.a   static version of libfoobar
libfoobar.so  shared version of libfoobar

main-static   executable program linked with libfoobar.a
main-shared   executable program linked with libfoobar.so

In order to execute the statically linked example

$ ./main-static

In order to execute the dynamically linked example:

   if you haven't done yet: (only once)

$ export LD_LIBRARY_PATH=.

and then

$ ./main-shared

The reason to set LD_LIBRARY_PATH=. is because the dynamic loader
does not search for libraries out in the current directory by default.





