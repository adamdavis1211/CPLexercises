#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#define MAXWORD 100
#define NOISEWORDS 17

/* Write a cross-referencer that prints a list of all words in a document, and for each word, 
a list of the line numbers on which it occurs. Remove noise words like "the", "and", and 
so on. */

char *noisew[] = { 	
	"the", "and", "a", "an", "of", "it",
	"was", "is", "to", "in", "on", "but",
	"did", "not", "then", "again", "into"
};

struct lnode {
	int lineno;
	struct lnode *next;
};

struct tnode {
	char *word;
	struct lnode *head;
	struct tnode *left;
	struct tnode *right;
};

int lineno = 1;
int getword(char *w, int max);
struct tnode *addtree(struct tnode *p, char *w);
void putlineno(struct lnode **k);
struct lnode *lalloc(void);
struct tnode *talloc(void);
char *mystrdup(char *s);
void printlines(struct lnode *k);
void treeprint(struct tnode *p);
int noiseword(char *w);

int main() {
	struct tnode *root;
	char word[MAXWORD];

	root = NULL;
	while (getword(word, MAXWORD) != EOF)
		if (isalpha(word[0]) && !noiseword(word))
			root = addtree(root, word);
	treeprint(root);
	return 0;
}

int noiseword(char *w)
{
	int i;

	for (i = 0; i < NOISEWORDS; i++)
		if (strcmp(w, noisew[i]) == 0)
			return 1;
	return 0;
}

struct tnode *addtree(struct tnode *p, char *w)
{
	int cond;

	if (p == NULL) {
		p = talloc();
		p->word = mystrdup(w);
		p->left = p->right = NULL; 
		p->head = NULL;
		putlineno(&p->head);
	} else if ((cond = strcmp(w, p->word)) == 0) 
		putlineno(&p->head);
	else if (cond < 0)
		p->left = addtree(p->left, w);
	else
		p->right = addtree(p->right, w);
	return p;
}

void putlineno(struct lnode **k)
{
	if (*k == NULL) 
		*k = lalloc();
	else if ((*k)->lineno == lineno)
		return;
	else
		putlineno(&((*k)->next));
}

struct lnode *lalloc(void)
{
	struct lnode *k = (struct lnode *) malloc(sizeof(struct lnode));
	k->lineno = lineno;
	k->next = NULL;
	return k;
}


struct tnode *talloc(void)
{
	return (struct tnode *) malloc(sizeof(struct tnode));
}


char *mystrdup(char *s)
{
	char *p;

	p = (char *) malloc(strlen(s)+1);	/* +1 for '\0' */ 
	if (p != NULL)
		strcpy(p, s);
	return p;
}

void treeprint(struct tnode *p)
{
	if (p == NULL)
		return;
	else
		treeprint(p->left);
	printf("%s: ", p->word);
	printlines(p->head);
	putchar('\n');
	treeprint(p->right);
}

void printlines(struct lnode *k)
{
	if (k == NULL)
		return;
	else
		printf("%d, ", k->lineno);
	printlines(k->next);
}
	
