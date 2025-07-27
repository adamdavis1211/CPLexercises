#include <limits.h>
#include <stdio.h>
#include <ctype.h>
#define MAX 1000
/* Adapt the ideas of printd to write a recursive version of itoa;
that is, convert an integer into a string by calling a recursive
routine. */

void itoa(int n, char s[]);

main() {
	char s[MAX];
	itoa(INT_MIN+1, s);
	printf("%s\n", s);
}

/* itoa: convert n to characters in s */
void itoa(int n, char s[]) {
	int j;
	static int i = 0;

	j = i;
	if (n < 0) {
		s[i++] = '-';
		n = -n;
	}	
	if (n / 10)
		itoa(n / 10, s);
	s[i++] = n % 10 + '0';
	if (j == 0) {
		s[i] = '\0';
		i = 0;
	}	
}
