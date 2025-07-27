#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#define DEFAULT_TABSTOP 8

/* Extend detab to accept the shorthand 
entab -m +n
to mean tab stops every n columns, starting at column m. */

int main(int argc, char *argv[]) 
{
	int c, i, j, colarg, tstop, tab;
	char *t;
	
	tab = DEFAULT_TABSTOP;
	colarg = tstop = 0;

	if (argc > 2) {
		if (*(t = argv[1]) == '-') {
			while (*(++t))
				if (!isdigit(*t)) {
					printf("Usage: detab -m +n\n");
					return -1;
				}
			colarg = atoi(argv[1]+1);
		}
		if (*(t = argv[2]) == '+') {
			while (*(++t))
				if (!isdigit(*t)) {
					printf("Usage: detab -m +n\n");
					return -1;
				}
			tstop = atoi(argv[2]+1);
		}
		else {
			printf("Usage: dtab -m +n\n");
			return -1;
		}
	}
	else if (argc == 2) {
			printf("Usage: dtab -m +n\n");
			return -1;
		}
	

	i = 0;
	while ((c = getchar()) != EOF) {
		if (c == '\t') {
			if (i >= colarg)
				tab = tstop;
			for (j = tab - (i % tab); j > 0; --j) {
				++i;
				putchar(' ');		
			}	
		}
		else if (c == '\n') {
				putchar(c);
				i = 0;
		}	
		else {
			putchar(c);
			++i;
		}
	}	
}
