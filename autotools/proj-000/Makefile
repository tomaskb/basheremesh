
NAME="\"AutoHello\""

all: hello

hello : main.o foo.o bar.o
	gcc -Wall $^ -o $@

hello: foobar.h

%.o : %.c
	gcc -I. -DPACKAGE_STRING=$(NAME) -Wall -c $< 

.PHONY: clean

clean:
	rm -f *.o hello
