#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define TAB 8

enum { BLANK, NONBLANK };

/* Extend entab and detab to accept the shorthand
entab -m +n 
to mean tabstops every n colunmns, starting at column m. */

int ch_req(int, int);

int main(int argc, char *argv[]) 
{
	int col, spcs, state, c, k, s, i, colarg, tstop, tab;
	char *t;
	col = 0;		/* current column, resets to 0 after '\n' is encountered */
	spcs = 0; 		/* count of how many consecutive spaces occur */
	colarg = tstop = 0;
	tab = TAB;
	state = NONBLANK;
	
	if (argc > 2) {
		if (*(t = argv[1]) == '-') {
			while (*(++t))
				if (!isdigit(*t)) {
					printf("Usage: entab -m +n\n");
					return -1;
				}
			colarg = atoi(argv[1]+1);
		}
		if (*(t = argv[2]) == '+') {
			while (*(++t))
				if (!isdigit(*t)) {
					printf("usage: entab -m +n\n");
					return -1;
				}
			tstop = atoi(argv[2]+1);
			printf("m = %d, n = %d\n", colarg, tstop);
		}
		else {
			printf("Usage: entab -m +n\n");
			return -1;
		}
	}
	else if (argc == 2) {
		printf("Usage: entab -m +n\n");
		return -1;
	}

	while ((c = getchar()) != EOF) {
		if (c == ' ' && state == NONBLANK) {	
			s = col;
			spcs++;
			state = BLANK;
		}
		else if (c == ' ' && state == BLANK) 
			spcs++;
		else if (c != ' ' && state == BLANK) {
			if (colarg && s < colarg)
				tab = TAB;
			else if (colarg && s >= colarg)
				tab = tstop;
			while (spcs >= (k = ch_req(s, tab))) {
				putchar('\\');
				putchar('t');
				spcs -= k;
				s += k;
			}
			for (; spcs > 0; spcs--) 
				putchar('#');
			putchar(c);
			state = NONBLANK;
		}
		else {
			putchar(c);
		}
		if (c == '\n')
			col = 0;
		else 
			col++;
	}
}
			
				
int ch_req(int col, int tab)		/* return number of characters until next tabstop */ 
{
	int i; 
	if (tab == 0)
		tab = 8;
	for (i = col+1; i % tab != 0; i++);
	return i - col;
}
