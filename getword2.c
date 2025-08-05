#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "ch.h"
#include "getword2.h"

#define TYPES 2

extern int type;

char *types[] = { "int", "char" };

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
			if (*w == ';')
				type = LASTNAME;
			ungetch(*w);
			break;
		}
	*w = '\0';
	for (c = 0; c < TYPES; c++) 
		if (strcmp(word, types[c]) == 0)
			type = NAME;
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
	case '#':
		while (getch() != '\n')
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

