#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "ch.h"
#define HASHSIZE 101
#define MAXWORD 100

struct nlist {		/* table entry */
	struct nlist *next;	/* next entry in chain */
	char *name;		/* defined name */
	char *defn;		/* replacement text */
};

static struct nlist *hashtab[HASHSIZE];
unsigned hash(char *s);
struct nlist *lookup(char *s);
struct nlist *install(char *name, char *defn);
char *mystrdup(char *s);


int main()
{
	char name[MAXWORD], defn[MAXWORD], word[MAXWORD], *w, dog;	
	struct nlist *node;
	int c, i = 0;

	while ((c = getch()) != EOF) {
		if (c == '#') {
			putchar(c);
			while (isalpha(c = getch()))	/* skip define keyword */
				putchar(c);
			putchar(c);
			while (isspace(c = getch()))
				putchar(c);
			putchar(c);
			if (isalpha(c)) {		/* store name */
				name[i++] = c;
				for (; isalnum(c = getch()); i++) {
					putchar(c);
					name[i] = c;
				}
				putchar(c);
				name[i] = '\0';
				i = 0;
			}
			while (isspace(c = getch()))
				putchar(c);
			putchar(c);
			if (isalnum(c)) {		/* store definition */
				defn[i++] = c;
				for (; (c = getch()) != ' ' && c != '\n'; i++) {
					putchar(c);
					defn[i] = c;
				}
				putchar(c);
				defn[i] = '\0';
				i = 0;
			}
			struct nlist *node = install(name, defn);
		} else if (isalpha(c)) {
			i = 0;
			word[i++] = c;
			while (isalpha(word[i] = getch())) 
				i++;
			dog = word[i];
			word[i] = '\0';
			i = 0;
			if (node = lookup(word)) {
				w = node->defn;
				while (*w)
					putchar(*w++);
			}
			else
				while (word[i])
					putchar(word[i++]);
			putchar(dog);

		}
		else if (c == '/') {
			putchar(c);
			if ((c = getch()) == '*') {
				putchar(c);
				while ((c = getch()) != EOF) {
					putchar(c);
					if (c == '*')
						if ((c = getch()) == '/') {
							putchar(c);
							break;
						}
						else
							putchar(c);
				}
			} else 
				putchar(c);
		}
		else
			putchar(c);
	}
}

	

/* hash:  form hash value for string s */
unsigned hash(char *s)
{
	unsigned hashval;

	for (hashval = 0; *s != '\0'; s++)
		hashval = *s + 31 * hashval;
	return hashval % HASHSIZE;
}

/* lookup:  look for s in hashtab */
struct nlist *lookup(char *s)
{
	struct nlist *np;

	for (np = hashtab[hash(s)]; np != NULL; np = np->next)
		if (strcmp(s, np->name) == 0)
			return np;	/* found */
	return NULL;		/* not found */
}

struct nlist *lookup(char *);
char *mystrdup(char *);

/* install:  look for s in hashtab */
struct nlist *install(char *name, char *defn)
{
	struct nlist *np;
	unsigned hashval;

	if ((np = lookup(name)) == NULL) { 	/* not found */
		np = (struct nlist *) malloc(sizeof(*np));
		if (np == NULL || (np->name = mystrdup(name)) == NULL)
			return NULL;
		hashval = hash(name);
		np->next = hashtab[hashval];
		hashtab[hashval] = np;
	} else
		free((void *) np->defn);
	if ((np->defn = mystrdup(defn)) == NULL)
		return NULL;
	return np;
}

int undef(char *name)
{
	struct nlist *np, *prev;
	

	np = prev = hashtab[hash(name)];
	if (np == NULL)
		return 0;
	if (strcmp(name, np->name) == 0) {
		if (np->next == NULL) {
			free(np->name); free(np->defn); free(np);
			hashtab[hash(name)] = NULL;
			return 1;
		} else {
			hashtab[hash(name)] = np->next;
			free(np->name); free(np->defn); free(np);
			return 1;
		}
	}
	while (strcmp(np->name, name) != 0) {
		prev = np;
		np = np->next;
		if (np == NULL)
			return 0;
	}
	prev->next = np->next;
	free(np->name); free(np->defn); free(np);
	return 1;
}
	

char *mystrdup(char *s)
{
	char *p;

	p = (char *) malloc(strlen(s)+1);	/* +1 for '\0' */ 
	if (p != NULL)
		strcpy(p, s);
	return p;
}
