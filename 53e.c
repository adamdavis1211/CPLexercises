#include <stdio.h>
#define MAX 1000

/* Write a pointer version of the function strcat that we showed in 
 * Chapter 2: strcat(s, t) copies the string to to the end of s. */

void v2strcat(char *, char *);
void get_line(char *s, int lim);

int main() {
	char t[MAX];
	char s[] = "appended: ";

	get_line(t, MAX);	
	printf("%s", t);
	v2strcat(s, t);
	printf("%s", s);
	return 0;
}

/* strcat: concatenate t to the end of s; s must be big enough */
void v1strcat(char s[], char t[]) {
	int i, j;

	i = j = 0;
	while (s[i] != '\0') /* find end of a s*/
		i++;
	while ((s[i++] = t[j++]) != '\0') /* copy t */
		;
}

void v2strcat(char *s, char *t) {
	while (*s)
		s++;
	while (*s++ = *t++);
}

void get_line(char *s, int lim) {
	int i, c;

	i = 0;
	while ((c = getchar()) != EOF && i < lim-1) {
		*(s+i++) = c;		
	}
	*(s+i) = '\0';
}
		
