/* Modify the pattern finding program of Chapter 5 to take its input from a set of 
named files or, if no files are named as arguments, from the standard input. 
Should the file name be printed when a matching line is found? */

#include <stdio.h>
#include <string.h>
#define MAXLINE 1000

/* find:  find pattern in provided named files or standard input */
/* USAGE: find [pattern] [opt file_1] [opt ...] [opt file_n] */
int main(int argc, char *argv[])
{
	FILE *fp;
	char buf[MAXLINE];
	int lineno = 1;

	if (argc < 2) {
		printf("Usage: find [pattern] [opt file_1] [opt ...] [opt file_n]\n");
		return -1;
	} else if (argc == 2) {
		while (fgets(buf, MAXLINE, stdin)) {
			if (strstr(buf, argv[1]))
				printf("stdin; line %d: %s", lineno, buf);
			lineno++;
		}
		lineno = 1;
	}
	else {
		while (--argc > 1) {
			fp = fopen(argv[argc], "r");
			while (fgets(buf, MAXLINE, fp)) {
				if (strstr(buf, argv[1]))
					printf("file %s; line %d: %s", argv[argc], lineno, buf);
				lineno++;
			}
			fclose(fp);
			lineno = 1;
		}
	}
}
