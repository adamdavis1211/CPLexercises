#include <stdio.h>
#define TABSTOP 3

/* replace each tab with spaces until next tab stop */
int main() {
	int c, i, j;

	i = 0;
	while ((c = getchar()) != EOF) {
		if (c == '\t') 
			for (j = TABSTOP - (i % TABSTOP); j > 0; --j) {
				++i;
				putchar(' ');		
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
