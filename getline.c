#include <stdio.h>
#include <ctype.h>
#include "ch.h"

extern int lineno;

int getword(char *w, int max)
{
	int c;

	while ((c = getch()) != EOF) {
		if (c == '\n') 
			lineno++;
		else if (isalpha(c)) {
			*w++ = tolower(c);
			while (isalpha(c = getch()))
				*w++ = tolower(c);
			*w = '\0';
			ungetch(c);
			return *w;
		}
	}
	return c;
}

