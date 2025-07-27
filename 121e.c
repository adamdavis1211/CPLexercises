#include <stdio.h>
#define TAB 8

enum { BLANK, NONBLANK };

/* Write a program entab that replaces strings of blanks by the minimum number of tabs 
and blanks to achieve the same spacing. When either a tab or a single blank would 
suffice to reach a tab stop, which should be given preference? */

int ch_req(int);

int main() 
{
	int col, spcs, state, c, k, s;
	col = 0;		/* current column, resets to 0 after '\n' is encountered */
	spcs = 0; 		/* count of how many consecutive spaces occur */
	state = NONBLANK;
	
	while ((c = getchar()) != EOF) {
		if (c == ' ' && state == NONBLANK) {	
			s = col;
			spcs++;
			state = BLANK;
		}
		else if (c == ' ' && state == BLANK) 
			spcs++;
		else if (c != ' ' && state == BLANK) {
			while (spcs >= (k = ch_req(s))) {
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
			
				
int ch_req(int col)		/* return number of characters until next tabstop */ 
{
	int i; 

	for (i = col+1; i % TAB != 0; i++);
	return i - col;
}
