#include <stdio.h>
#include <ctype.h>
#include "ch.h"
#include "getword.h"

int getword(char *word, int lim)
{
	int c, skips(void);
	char *w = word;

	while (skips())
		;
	while (isspace(c = getch()))
		;
	if (isspace(c))
		while (isspace(c = getch()))
			;
	if (c != EOF)
		*w++ = c;
	if (!isalpha(c) && c != '_') {
		*w = '\0';
		return c;
	}
	for ( ; --lim > 0; w++)
		if (!isalnum(*w = getch()) && *w != '_') {
			ungetch(*w);
			break;
		}
	*w = '\0';
	return word[0];
}

int skips(void)
{
	int c;

	while (isspace(c = getch()))
		;
	switch (c) {
	case '"':
		while (getch() != '"')
			;
		break;
	case '/': 
		if ((c = getch()) == '*') 
			for ( ; (c = getch()) != EOF; )
				if (c == '*') {
				       if ((c = getch()) == '/')
						break;
				       else
					       ungetch(c);
				}
		else {
			ungetch('/');
			ungetch(c);
			return 0;
		}
	default: 
		ungetch(c);
		return 0;
	}
	return 1;
}

