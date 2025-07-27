#include <stdio.h>
#define NUMBER 0
/* Rewrite appropriate programs from eariler chapters and exercises with 
 * pointers instead of array indexing. Good possibilities include getline
 * (Chapters 1 and 4), atoi, itoa, and their variants (Chapters 2, 3, and 4),
 * reverse (Chapter 3), and strindex and getop (Chapter 4). */

void get_line(char *s, int lim);
int atoi(const char *s);
int getop(char s[]);
int strindex(char *s, char *t);
void reverse(char *s);

char search[] = "123456789";
char str[] = "012345this";

void main() {
	reverse(search);
	printf("%s\n", search);

}

void get_line(char *s, int lim) {
	int i, c;
	
	i = 0;
	while ((c = getchar()) != EOF && i < lim-1)
		*(s+i++) = c;
	*(s+i) = '\0';
}

#define BUFSIZE 100
#include <ctype.h>
int buf[BUFSIZE];
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

int getop(char s[]) {
	int i, c;

	while ((s[0] = c = getch()) == ' ' || c == '\t')
		;
	s[1] = '\0';
	if (!isdigit(c) && c != '.')		
		return c;	/* not a number */
	i = 0;
	if (isdigit(c)) 	/* collect integer part */
		while (isdigit(s[++i] = c = getch()))
			;
	if (c == '.')		/* collect fraction part */
		while (isdigit(s[++i] = c = getch()))
			;
	s[i] = '\0';
	if (c != EOF)
		ungetch(c);
	return NUMBER;
}

int getopv2(char *s) { /* pointer version */
	int c;

	while ((*s = c = getch()) == ' ' || c == '\t')
		;
	*(s+1) = '\0';
	if (!isdigit(c) && c != '.')
		return c;
	if (isdigit(c))
		while (isdigit(*(++s) = c = getch()))
			;
	if (c == '.')
		while (isdigit(*(++s) = c = getch()))
			;
	*s = '\0';
	if (c != EOF)
		ungetch(c);
	return NUMBER;
}


int strindex_arr(char s[], char t[]) {
	int i, j, k;

	for (i = 0; s[i] != '\0'; i++) {
		for (j=i, k=0; t[k]!='\0' && s[j]==t[k]; j++, k++)
			;
		if (k > 0 && t[k] == '\0')
			return i;
	}
	return -1;		
}



int strindex(char *s, char *t) {
	char *i, *j;
	int k;

	for (i = s; *i != '\0'; i++) {
		for (j=i, k=0; *(t+k) != '\0' && *j == *(t+k); j++, k++)
			;
		if (k>0 && *(t+k) == '\0')
			return i - s;
	}
	return -1;
}

#include <string.h>

void reverse_arr(char s[]) {
	int c, i, j;

	for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}


void reverse(char *s) {
	char c, *i;
	int j;

	for (i = s, j = strlen(s)-1; (i-s) < j; i++, j--) {
		c = *i;
		*i = *(s+j);
		*(s+j) = c;
	}
}
