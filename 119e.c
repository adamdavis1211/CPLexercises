#include <stdio.h>
#define MAX 1000

void clearstr(char s[]);
void reverse(char s[], int size);

/* reverse input a line at a time */
int main() { 
	int c, i;
	char str[MAX];
	clearstr(str);

	i = 0;
	while ((c = getchar()) != EOF) {
		if (c == '\n') {
			str[i] = c;
			reverse(str, i-1);
			printf("%s", str);
			clearstr(str);
			i = 0;
		}
		else {
			str[i] = c;
			++i;
		}
	}
}

/* reverse s in place */
void reverse(char s[], int size) {
	int i, n, tmp;

	i = 0;
	n = size;
	while (n - i >= 1) {
		tmp = s[n];
		s[n] = s[i];
		s[i] = tmp;
		++i;
		--n;	
	}
}	

/* clear the string */ 
void clearstr(char s[]) {
	int i;

	for (i = 0; i < MAX; ++i)
		s[i] = '\0';
}	
