#include <stdio.h>
#define THRESHOLD 80
#define MAXSIZE 1000

void clearstr(char str[]);
int get_line(char str[], int lim); 

/* print all input lines that are longer than 80 characters */
int main() {
	int c, count, linesize;
	char str[MAXSIZE];	

	while ((linesize = get_line(str, MAXSIZE)) > 0) 
		if (linesize > 80)	
			printf("%d line: %s", linesize, str);
	return 0;
}

int get_line(char str[], int lim) {
	int c, i, j;

	j = 0;
	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i) 
		str[i] = c;
	if (c != '\n')
		while ((c = getchar()) != EOF && c != '\n')
			++j;
	if (c == '\n') {
		str[i] = c;
		++i;
	}
	str[i] = '\0';
	return i + j;
}

/* clear a string */

void clearstr(char str[]) {
	int i;
	
	for (i = 0; str[i] != '\0' && i < MAXSIZE; ++i) 
		str[i] = '\0';	
}
			
