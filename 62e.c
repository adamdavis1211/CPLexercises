#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "getword.h"

#define MAXWORD 100
/* Exercise 6-2. Write a program that reads a C program and prints in alphabetical order each
group of variable names that are identical in the first 6 characters, but different somewhere
thereafter. Don't count words within strings and comments. Make 6 a parameter that can be 
set from the command line. */

struct tnode {		/* the tree node */
	char *word;	/* points to the text */
	struct tnode *left;	/* left (nonrelated word) child */
	struct tnode *right;	/* right (nonrelated word) child */
	
	struct tnode *leftrel;		/* left child (related word) */
	struct tnode *rightrel;		/* right child (related word) */
};

struct tnode *talloc(void);
struct tnode *findrelated(struct tnode *p, char *w, int charno);
struct tnode *findposition(struct tnode *p, char *w);
char *mystrdup(char *s);
void printsubtree(struct tnode *p);

int main(int argc, char *argv[])
{
	struct tnode *root;
	char word[MAXWORD];
	int nochar;

	if (argc > 1)
		nochar = atoi(argv[1]+1);
	else 
		nochar = 6;

	root = NULL;
	while (getword(word, MAXWORD) != EOF)
		if (isalpha(word[0]))
			root = findrelated(root, word, nochar);
	
	return 0;
}

struct tnode *findrelated(struct tnode *p, char *w, int nochar)
{
	int cond;

	if (p == NULL) {
		p = talloc();
		p->word = mystrdup(w);
		p->left = p->right = NULL;
	} else if ((cond = strncmp(w, p->word, nochar)) == 0) 
		return findposition(p, w);
	else if (cond < 0)
		p->left = findrelated(p->left, w, nochar);
	else
		p->right = findrelated(p->right, w, nochar);
	return p;
}

struct tnode *findposition(struct tnode *p, char *w)
{
	int cond;

	if (p == NULL) {
		p = talloc();
		p->word = mystrdup(w);
		p->leftrel = p->rightrel = NULL;
	} else if ((cond = strcmp(w, p->word)) == 0)
		return p;
	else if (cond < 0)
		p->leftrel = findposition(p->leftrel, w);
	else
		p->rightrel = findposition(p->rightrel, w);
	return p;
}

char *mystrdup(char *s)
{
	char *p;

	p = (char *) malloc(strlen(s)+1);	/* +1 for '\0' */ 
	if (p != NULL)
		strcpy(p, s);
	return p;
}

/* talloc:  make a tnode */
struct tnode *talloc(void)
{
	return (struct tnode *) malloc(sizeof(struct tnode));
}


void printsubtree(struct tnode *p)
{
	if (p == NULL)
		return;
	else
		printsubtree(p->leftrel);
	printf("%s\n", p->word);
	printsubtree(p->rightrel);
}	
