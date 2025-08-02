#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100
#define NKEYS (sizeof keytab / sizeof keytab[0])

/* Our viersion of getword does not properly handle underscores, string constants,
 * comments, or preprocessor control lines. Write a better version. */

struct key {
	char *word;
	int count;
} keytab[] = {
	"auto", 0,
	"break", 0,
	"case", 0,
	"char", 0,
	"const", 0,
	"continue", 0,
	"default", 0,
	/* ... */
	"unsigned", 0,
	"void", 0,
	"volatile", 0,
	"while", 0,
};

int getword(char *, int);
int binsearch(char *, struct key *, int);

/* count C keywords */
int main()
{
	int n;
	char word[MAXWORD];

	while (getword(word, MAXWORD) != EOF)
		if (isalpha(word[0]))
			if ((n = binsearch(word, keytab, NKEYS)) >= 0)
				keytab[n].count++;
	for (n = 0; n < NKEYS; n++)
		if (keytab[n].count > 0)
			printf("%4d %s\n", keytab[n].count, keytab[n].word);
	return 0;
}

/* binsearch:  find word in tab[0]...tab[n-1] */
int binsearch(char *word, struct key tab[], int n)
{
	int cond;
	int low, high, mid;

	low = 0;
	high = n - 1;
	while (low <= high) {
		mid = (low+high) / 2;
		if ((cond = strcmp(word, tab[mid].word)) < 0)
			high = mid -1;
		else if (cond > 0)
			low = mid + 1;
		else
			return mid;
	}
	return -1;
}

#include "ch.h"
/* getword:  get next word or character from input */
/* int getword(char *word, int lim)
{
	int c, getch(void);
	void ungetch(int);
	char *w = word;

	while (isspace(c = getch()))
		;
	if (c != EOF)
		*w++ = c;
	if (!isalpha(c)) {
		*w = '\0';
		return c;
	}
	for ( ; --lim > 0; w++)
		if (!isalnum(*w = getch())) {
			ungetch(*w);
			break;
		}
	*w = '\0';
	printf("%s\n", word);
	return word[0];
} */

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
	printf("%s\n", word);
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

