#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "dcl.h"
#include "ch.h"

#define MAXTOKEN  100
#define TYPES     5
#define MAXWORDS 10

/* (518e.c) make dcl recover from input errors */
/* (520e.c) Expand dcl to handle declarations with function argument types,
qualifiers like const, and so on. */

int gettoken(void);
int tokentype;			/* type of last token */
char token[MAXTOKEN];		/* last token string */
char name[MAXTOKEN];		/* indentifier name */
char datatype[MAXTOKEN];	/* data type = char, int, etc. */
char qualifier[MAXTOKEN];
char parambuf[MAXTOKEN];	/* buffer holding function parameters */
char out[1000];
int err_state, v;
char *quals[] = { "const", "volatile" }; /* type qualifier */
char *types[TYPES] = { "int", "float", "char", "long", "double" }; /* types */
int validparam(void);

int main()	/* convert declaration to words */
{
	err_state = NOERROR;
	while (gettoken() != EOF) {		/* 1st token on line is the datatype or qual */
		qualifier[0] = '\0';
		if (!strcmp(token, quals[0]) || !strcmp(token, quals[1])) {
			strcpy(qualifier, token);
			gettoken(); 
		}
		strcpy(datatype, token);	
		out[0] = '\0';
		dcl();		/* parse rest of line */
		if (tokentype != '\n') {
			err_state = ERROR;
			printf("syntax error\n");
		}
		printf("%s: %s %s %s\n", name, out, qualifier, datatype);
		if (err_state) {
			while ((v = gettoken()) != '\n' && v != EOF);
			err_state = NOERROR;
		}
	}
	return 0;
}

int gettoken(void)	/* return next token */
{
	int c, getch(void), i = 0;
	void ungetch(int);
	char *p = token, *jj = parambuf;
	
	while ((c = getch()) == ' ' || c == '\t')
		;
	if (c == '(') {
		if (validparam()) {
			strcpy(token, parambuf);
			return tokentype = PARENS;
		} else {
			while (*++jj)
				ungetch(*jj);
			return tokentype = '(';
		}
	} else if (c == '[') {
		for (*p++ = c; (*p++ = getch()) != ']'; )
			;
		*p = '\0';
		return tokentype = BRACKETS;
	} else if (isalpha(c)) {
		for (*p++ = c; isalnum(c = getch()); )
			*p++ = c;
		*p = '\0';
		ungetch(c);
		return tokentype = NAME;
	} else 
		return tokentype = c;
}

enum { NONWORD, WORD };

int validtype(char *);

int validparam(void)
{
	int c, i = 0, j = 0, error = 0, state = NONWORD;
	char word[MAXTOKEN];

	parambuf[i++] = '(';
	while ((c = getch()) != ')') {
		parambuf[i++] = c;
		if (state == NONWORD && isalpha(c)) {
			state = WORD;
			word[j++] = c;
		}
		else if (state == NONWORD && (c == '*' || c == '(')) {
			parambuf[i] = '\0';
			return 0;
		}
		else if (state == WORD && (isalpha(c) || c == '*')) 
			word[j++] = c;
		else if (state == WORD) { 
			word[j] = '\0';
			if (validtype(word)) {
				state = NONWORD;
				j = 0;
			}
			else {
				parambuf[i] = '\0';
				return 0;
			}
		}
	}
	parambuf[i++] = c;
	parambuf[i] = '\0';
	return 1;
}

int validtype(char *word)
{
	int i;

	for (i = 0; i < TYPES; i++)
		if (!strcmp(word, types[i]))
			return 1;
	return 0;	
}
		
			
		
			



