#include <ctype.h>
#include <stdio.h>
#define MAXLINE 60

/* Write a program that will print arbitrary input in a sensible way. 
As a minimum, it should print non-graphic characters in octal or hexadecimal
according to local custom, and break long text lines. */

int main()
{
	int c, i = 0;

	while ((c = getchar()) != EOF) {
		if (i++ == MAXLINE) {
			putchar('\n');
			i = 0;
		}
		if (iscntrl(c))
			printf("\\x%02X", c);
		else
			printf("%c", c);
	}
}
