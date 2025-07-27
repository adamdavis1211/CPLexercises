#include <stdio.h>
#define MAX 1000

int get_line(char s[], int lim);
int my_htoi(char s[]);

int main() {
	int d;
	char s[MAX];		/* input string */

	while ((d = get_line(s, MAX)) != 0) {
		d = my_htoi(s);
		printf("%d\n", d);
	}

}

int get_line(char s[], int lim) {
	int c, i;

	for (i = 0; i < lim-1 && (c = getchar()) != '\n' && c != '\0'; ++i) 
		s[i] = c;
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i; 
}

int my_htoi(char s[]) {
	int i, n, l, off;

	n = off = l = 0;
	if (s[off] == '0') 
		++off;
	if (s[off] == 'x' || s[off] == 'X')
		++off;
	for (i = off; (s[i] >= 'A' && s[i] <= 'F') || (s[i] >= 'a' && s[i] <= 'f') || (s[i] >= '0' && s[i] <= '9'); ++i) {
		if (s[i] >= 'A' && s[i] <= 'F') 
			l = s[i] - 55;
		else if (s[i] >= '0' && s[i] <= '9')
			l = s[i] - 48;
		else if (s[i] >= 'a' && s[i] <= 'f')
			l = s[i] - 87;
	
		n = 16 * n + l;
	}
	return n;			
}
