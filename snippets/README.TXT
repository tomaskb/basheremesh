
POSIX snippets.

To build the examples: run 'make'.

These are very simple examples of POSIX functions usage:

fork.c		        Process duplication example
exec.c			Replaces a process' image
crash.c			A trivial example of fork & exec usage
ioredirect.c		Input/Output redirection
pipe.c			Example of IPC with pipe
pipe2			More elaborated example of pipe, with redirection	
pipeline		Recursive pipeline execution.
signal.c		Asynchronous signal manipulation, com signal()
signal2.c		Better signal manipulation with sigaction()
toggle-output.c		Toggle output from tty to a file and then back to tty
token.c			Extract tokens from a string	

Some auxiliary programs used by the former examples:

loop.c			Auxiliary program for exec example




