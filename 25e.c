#include <stdio.h>
#include "util.h"
#define MAX 1000

int any(char s1[], char s2[]);

/* Write the function any(s1, s2), which returns the first location
in a string s1 where any character from the string s2 occurs, or -1 
if s1 contains no characters from s2. */

int main() {
	int d, k, l;
	char s[MAX], t[MAX];

	while ((d = get_line(s, MAX)) > 0 && ((k = get_line(t, MAX)) > 0)) {
		l = any (s, t);
		printf("character: %d\n", l+1);	
	}
}

int any(char s1[], char s2[]) {
	int i, j;

	for (i = 0; s1[i] != '\0'; i++) {
		for (j = 0; s2[j] != '\0' && s1[i] != s2[j]; ++j);
		if (s2[j] != '\0')
			return i;	
	}
	return -1;
}

