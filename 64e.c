#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "getword.h"
#define MAXWORDS 1000
#define MAXWORD 100
/* Write a program that prints the distinct words in its input sorted into decreasing 
order of frequency of occurence. Precede each word by its count. */

struct wnode {
	char *w;		/* word */
	struct wnode *left;	/* left child */
	struct wnode *right;	/* right child */
	struct cnode *count;	/* pointer to node containing frequency of occurence */
};

struct cnode {
	char *w;
	int count;
};

int comp(const void *w, const void *t);
void printwords(void);
struct wnode *insertnode(struct wnode *p, char *w);
char *mystrdup(char *s);
struct wnode *walloc(char *w);
struct cnode cnodes[MAXWORDS];
int np = 0;		/* next free position in cnode array */

int main() 
{
	struct wnode *root;
	char word[MAXWORD], *w;
	int i;
	
	root = NULL;
	while (getword(word, MAXWORD) != EOF)
		if (isalpha(word[0])) {
			for (i = 0; word[i] = tolower(word[i]); i++);
			root = insertnode(root, word);
		}
	qsort(cnodes, np, sizeof(struct cnode), comp);
	printwords();	
	return 0;
}

struct wnode *insertnode(struct wnode *p, char *w)
{
	int cond;

	if (p == NULL) 
		p = walloc(w);
	else if ((cond = strcmp(w, p->w)) < 0)
		p->left = insertnode(p->left, w);
	else if (cond > 0)
		p->right = insertnode(p->right, w);
	else
		p->count->count++;
	return p;
}

struct wnode *walloc(char *w) 
{
	struct wnode *p = (struct wnode *) malloc(sizeof(struct wnode));
	p->left = p->right = NULL;
	p->w = mystrdup(w);
	p->count = cnodes + np++;
	p->count->w = p->w;
	p->count->count = 1;	/* first occurence of word */
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

void printwords(void)
{
	int i; 

	for (i = 0; i < np; i++)
		printf("%s: %d\n", (cnodes[i]).w, (cnodes[i]).count);
}

int comp(const void *w, const void *t)
{
	const struct cnode w1 = *(const struct cnode *) w;
	const struct cnode t1 = *(const struct cnode *) t;
	return t1.count - w1.count;
}

