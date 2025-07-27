#include "util.c"
#include <stdio.h>
#define MAX 1000

/* Write a function expand(sl,s2) that expands shorthand notations like a-z in the string s1 into the equivalent complete list abc...xyz in s2. Allow for letters of either case and digits, and be prepared to handle cases like a-b-c and a-z0-9 and -a-z. Arrange that a leading or trailing '-' is
taken literally. */

int main() {
	int c, i;
	char s1[MAX], s2[MAX];

	i = 0;
	while ((c = getchar()) != EOF && i < MAX-1) 
		s1[i++] = c;		
	s1[i] = '\0';
	expand(s1, s2);
}	
