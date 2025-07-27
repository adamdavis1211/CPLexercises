#include <stdio.h>
#include <ctype.h>
#define MAX 1000
/* As written, getint teats a + or - not followed by a digit as a valid
 * representation of zero. Fix it to push such a character back on the 
 * intput */

int getch(void);
void ungetch(int);
int getint(int *, int *);

main() {
	int i, s, arr[MAX];
	
	i = 0;
	while (i < MAX && getint(&arr[i], &i) != EOF);
	for (s = 0; s < i; printf("%d ", arr[s++]));
		
}

int getint(int *pn, int *i) {
	int c, sign;

	while (isspace(c = getch()))	/* skip white space */
		;
	if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
		ungetch(c);	/* it is not a number */
		return 0;
	}
	sign = (c == '-') ? -1 : 1;
	if (c == '+' || c == '-')
		c = getch();
	if (isdigit(c)) {
		(*i)++;
		for (*pn = 0; isdigit(c); c = getch())
			*pn =  10 * *pn + (c - '0');
		*pn *= sign;
	}
	if (c != EOF)
		ungetch(c);
	return c;
}

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch(void) {
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}
