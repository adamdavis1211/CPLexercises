#include <stdio.h>
#define MAX 1000
#define BLANK 1
#define NONBLANK 0

int get_line(char s[], int max);
void clearline(char s[]);

/* remove trailing blanks and tabs from each line of input, and
to delete entirely blank lines */
int main() { 
	int linesize;
	char str[MAX];
	
	clearline(str);
	while ((linesize = get_line(str, MAX) > 0))
		printf("%s", str);
		clearline(str);
	return 0;
}	

/* get line from FILE * stdin (keyboard) */
int get_line(char s[], int max) {
	int c, i, state;
	
	i = 0;
	state = NONBLANK;
	for (i = 0; i < max - 1 && (c = getchar()) != EOF && c != '\n'; ++i) {
		if (state == NONBLANK && c != ' ' && c != '\t')
			s[i] = c;
		if (state == NONBLANK && (c == ' ' || c == '\t')) {
			s[i] = c;
			state = BLANK;
		}
		if (state == BLANK && c != ' ' && c != '\t') {
			s[i] = c;
			state = NONBLANK;	
		}
	}		
	s[i] = '\n';
	s[i+1] = '\0';
	return i;
}

/* set all chars to '\0' */
void clearline(char str[]) {
	int i;
	
	for (i = 0; i < MAX; ++i)
		str[i] = '0';
}
