#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
#define MAXLINE 1000
#define DEFAULT_N 10
#define ERROR	printf("Usage: tail -n\n");
/* Write the program tail, which prints the last n lines of its input. 
By default, n is set to 10, let us say, but it can be changed by an 
optional argument so that 

tail -n

prints the last n lines. The program should behave rationally no 
matter how unreasonable the input or the value of n. Write the 
program so it makes the best use of available storage; lines 
should be stored as in the sorting program of Section 5.6, not
in a two-dimensional array of fixed size. */

int argtoi(char *, int *);
char *strex(char *one, char *two);

int main(int argc, char *argv[]) 
{	
	int n, line_no, line_size;
	char *t;

	n = DEFAULT_N;
	if (argc > 2) {
		ERROR;
		return -1;
	}
	if (argc > 1 && !argtoi(argv[1], &n)) {
		ERROR;
		return -1;
	}
	char *lines[n], storage[n*MAXLINE], buffer[MAXLINE], *temp;
	int len, i, p;

	p = line_no = 0;

	while ((len = get_line(buffer, MAXLINE)) > 0) {
		buffer[len-1] = '\0';
		if (line_no < n) {
			strcpy(storage+p, buffer);
			lines[line_no] = storage + p;
			p += len;
		}	
		else {
			for (i = 0; i < n-1; i++) {
				temp = strex(lines[i], lines[i+1]);
				lines[i+1] = temp;	
			}
			strcpy(temp, buffer);
		}	
		line_no++;	
	}
	if (line_no >= n) 	
		for (i = 0; i < n; i++)
			printf("%s\n", lines[i]);
	else
		for (i = 0; i < line_no; i++)
			printf("%s\n", lines[i]);

}

char *strex(char *one, char *two) 
{
	while (*one++ = *two++);
	return one;	
}

/* argtoi:  convert a commmand line argument to integer and store at int *result). 
 will check if first character is '-' and skip it if so or return return 0 if not. return 0 
if failed to convert. does not support negative numbers */

int argtoi(char *s, int *result) 	
{			
	char *t;

	if (*(t = s) != '-' || !isdigit(*++s))
		return 0;
	else
		while (*++s)
			if (!isdigit(*s))
				return 0;
	*result = atoi(++t);
	return 1;
}	
