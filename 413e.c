#include <stdio.h>

void reverse(char s[]);

/* Write a recursive version of the function reverse(s), which reverses the 
string s in place. */

main() {
	char s[] = "live";
	reverse(s);
	printf("%s\n", s);
}

void reverse(char s[]) {
	static int i, j = 0;
	char c;
	int t;

	t = i;
	if (s[i] == '\0') 
		return;
	else {
		c = s[i++];
		reverse(s);
	}
	s[j++] = c;	
	if (t == 0)
		i = j = 0;
}
