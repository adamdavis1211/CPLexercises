#include <stdio.h>
#include <ctype.h>
#define MAX 1000
/* Write getfloat, the floating-point analog of getint. What type 
 * dpes getfloat return as its function value? */

int getch(void);
void ungetch(int);
int myatof(float *, int *);

int main() {
	int i = 0;
	float arr[MAX];
	int s;

	while(myatof(&arr[i], &i) != EOF);
	for (s = 0; s < i; s++)
		printf("%g ", arr[s]);
	putchar('\n');
}

int myatof(float *fp, int *i) {
	float val, power;
	int c, sign, fl;

	fl = 0;
	while (isspace(c = getch()));
	if (!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.') 
		return 0;
	sign = (c == '-') ? -1 : 1;
	if (c == '+' || c == '-')
		c = getch();
	if (isdigit(c)) {
		fl = 1;
		(*i)++;
		for (val = 0.0; isdigit(c); c = getch())
			val = 10.0 * val + (c - '0');
		*fp = sign * val;
	}
	if (c == '.') {
		c = getch();
		for (power = 1.0; isdigit(c); c = getch()) {
			val = 10.0 * val + (c - '0');
			power *= 10;
		}
		if (!fl) 
			(*i)++;
		*fp = sign * val / power;
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
