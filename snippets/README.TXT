
Very simple examples of POSIX function usages.

Code snippets may come in handy as inspiration when implementing a simple POSIX 
shell with external command execution, IO redirection, pileline and job control.

debug.h	 		Examples use these macros for debugging 
eg-fork.c		Process duplication example
eg-exec.c		Replaces a process' image
loop.c			Auxiliary program for exec example
crash.c			A trivial example of fork & exec usage
eg-ioredirect.c		Input/Output redirection
eg-pipe.c		Example of IPC with pipe
eg-pipe2		More elaborated example of pipe, with redirection	
eg-pipeline		Recursive pipeline execution.
eg-signal.c		Asynchronous signal manipulation, com signal()
eg-signal-better.c	Better signal manipulation with sigaction()
toggle-output.c		Toggle output from tty to a file and then back to tty
token.c			Extract tokens from a string	

To build the examples: run 'make'.
