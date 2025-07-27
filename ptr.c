#include <stdio.h>

void swap(int *, int *);

main() {
	int x, y;
	
	x = 2;
	y = 3;
	swap(&x, &y);
	printf("x: %d, y: %d\n", x, y);
}

void swap(int *x, int *y) { 	
	int temp;
	
	temp = *x;
	*x = *y;
	*y = temp;
}

#include <ctype.h>
#include "ch.h"

/* getint: get next integer from input into *pn */
int getint(int *pn) {
	int c, sign;
	
	while (isspace(c = getch()))	/* skip white space */
		;
	if (!isdigit(c) && c != EOF && c!= '+' && c!= '-') {
		ungetch(c); 	/* it is not a number */
		return 0;
	}
	sign = (c == '-') ? -1 : 1;
	if (c == '+' || c == '-')
		c = getch();
	for (*pn = 0; isdigit(c), c = getch();)
		*pn = 10 * *pn + (c - '0');
	*pn *= sign;
	if (c != EOF)
		ungetch(c);
	return c;
}
	
