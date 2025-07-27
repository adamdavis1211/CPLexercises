#include <stdio.h>
#include <stdlib.h>
#define DEFAULT_TAB 8
#define IND(A, B) (A<B-1) ? A++ : A
	
enum { BLANK, NONBLANK };

/* Modify the program entab and detab (written as exercises in Chapter 1) to accept a 
list of tab stops as arguments. Use the default tab settings if there are no 
arguments */
	
int ch_req(int, int);

int main(int argc, char *argv[]) 
{
	int col, spcs, state, c, k, s, i, tabs[argc];
	col = 0;		/* current column, resets to 0 after '\n' is encountered */
	spcs = 0; 		/* count of how many consecutive spaces occur */
	state = NONBLANK;

	if (argc == 1)
		tabs[i=0] = DEFAULT_TAB;
	else {
		for (i = 1; argv[i] != NULL; i++)
			tabs[i-1] = atoi(argv[i]);
		i = 0;
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
			while (spcs >= (k = ch_req(s, tabs[IND(i, argc)])) && k >= DEFAULT_TAB) {
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
		if (c == '\n') {
			col = 0;
			i = 0;
		}
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
