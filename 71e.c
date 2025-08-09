/* Write a program that converts upper case to lower or lower case to upper,
depending on the name it is invoked with, as found in argv[0] */

#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char *argv[]) 
{
	int c;
	char *p;

	p = strrchr(argv[0], '/');
	p = p ? p + 1 : argv[0];	

	if (strstr(p, "lower"))
		while ((c = getchar()) != EOF)
			putchar(tolower(c));
	else if (strstr(p, "upper"))
		while ((c = getchar()) != EOF)
			putchar(toupper(c));
}
