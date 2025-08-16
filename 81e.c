/* Rewrite the program cat from Chapter 7 using read, write, open, and close instead
of their standard library equivalents. Perform experiments to determine the relative
speeds of the two versions */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#define STDIN 0
#define STDOUT 1

void error(char *fmt, ...);

int main(int argc, char *argv[])
{
	int srcfd, destfd, n;
	char buf[BUFSIZ];

	if (argc == 1) {
		srcfd = STDIN;		/* stdin */
		destfd = STDOUT;	/* stdout */
	} else if (argc == 2) 
		if ((srcfd = open(argv[1], O_RDONLY, 0)) == -1)
			error("cat: can't open %s\n", argv[1]);
		else 
			destfd = STDOUT;
	else if (argc == 3) {
		if ((srcfd = open(argv[1], O_RDONLY, 0)) == -1)
			error("cat: can't open %s\n", argv[1]);
		if ((destfd = open(argv[2], O_APPEND | O_WRONLY, 0)) == -1)
			error("cat: can't open %s\n", argv[2]);
		if (strcmp(argv[1], argv[2]) == 0)
			error("do not attempt same src and dst file\n");
	} else
		error("Usage cat [opt srcfile] [opt destfile]\n");

	while ((n = read(srcfd, buf, BUFSIZ)) > 0)
		write(destfd, buf, n);	
}
			
		



