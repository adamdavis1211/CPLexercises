#include <stdio.h>
#include <stdlib.h>
#define MAXARGS 10
#define DEFAULT_TAB 8

/* Modify the program detab to accept a list of tab stops as arguments. Use
the default tab settings if there are no arguments. */

int main(int argc, char *argv[]) {
	int c, i, j, k, tab_args, tabs[MAXARGS];

	k = 0;
	tab_args = 1;
	if (argc == 1)
		tabs[k] = DEFAULT_TAB;
	else {
		for (i = 1; i < argc; i++, k++)
			tabs[k] = atoi(argv[i]);
		tab_args = k;
	}

	
	i = k = 0;
	while ((c = getchar()) != EOF) {
		if (c == '\t') { 
			for (j = tabs[k] - (i % tabs[k]); j > 0; --j) {
				++i;
				putchar('#');		
			}	
			if (k < tab_args-1)
				k++;
		}
		else if (c == '\n') {
				putchar(c);
				i = k = 0;
		}	
		else {
			putchar(c);
			++i;
		}
	}	
}
