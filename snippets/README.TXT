
POSIX snippets.

To build the examples: run 'make'.

These are very simple examples of POSIX functions usage:

fork.c		        Process duplication example
exec.c			Replaces a process' image
crash.c			A trivial example of fork & exec usage
ioredirect.c		Input/Output redirection
pipe.c			Example of IPC with pipe
pipe2			Pipe, with redirection
pipeline                A two-command pipeline	
rpipeline		Recursive pipeline execution.
signal.c		Asynchronous signal handling old way
signal2.c		Asynchronous signal handling new way
siginfo.c		Example of sigaction's siginfo usage
toggle-io.c		Toggle output between two files
token.c			Extract tokens from a string	

Some auxiliary programs used by the former examples:

loop.c			Auxiliary program for exec example




