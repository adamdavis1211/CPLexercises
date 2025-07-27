#include "util.c"
#define MAX 1000

/* Write a function escape(s, t) that converts characters like newline 
and tab into visible escape sequences like \n and \t as it copies 
the string t to s. Use a switch. Write a function for the other 
direction as well, converting escape sequences into real characters. */

int main() {
	char s[MAX], t[MAX];
	int s_size, c, i;

	i = 0;
	while ((c = getchar()) != EOF && i < MAX-1) 
		s[i++] = c;
	s[i] = '\0';		

	s_size = escape(s, t, MAX);
	printf("%s", t);
	unescape(s, t, MAX);
	printf("\n%s", t);
	return 0;
}
