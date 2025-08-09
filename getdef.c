#include "ch.h"
#define NAME 1000
#define DEFN 2000

void preprocess(void)
{
	char name[MAXWORD], defn[MAXWORD];	
	int c, i = 0;

	while ((c = getch()) != EOF) {
		if (c == '#') {
			while (isalpha(c = getch()))	/* skip define keyword */
				;
			while (isspace(c = getch()))
				;
			if (isalpha(c)) {
				name[i++] = c;
				for (; isalnum(c = getch()); i++)
					name[i] = c;
				name[i] = '\0';
				i = 0;
			}
			while (isspace(c = getch()))
				;
			if (isalnum(c)) {
				defn[i++] = c;
				for (; isalnum(c = getch()); i++)
					defn[i] = c;
				defn[i] = '\0';
				i = 0;
			}
			struct nlist *node = install(name, defn);
			if (node == NULL)
				printf("problem\n");
			else printf("%s\n", node->name);
			else printf("%s\n", node->defn);
		}
	}
}
