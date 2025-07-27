#include <stdio.h> 
#define MAX 1000

/* Write versions of the library functions strncpy, strncat, and strncmp, 
 * which operate on at most the first n characters of their argument strings.
 * For example, strncpy(s, t, n) copies at most n characters of t to s. Full
 * descriptions are in Appendix B. */

/* copy at most n characters of string ct to s; return s. Pad with null 
 * terminators if ct has fewer than n characters */
char *my_strncpy(char *s, const char *ct, int n);

/* concatenate at most n characters of string ct to string s, terminate s
 * with null terminator; return s; */
char *my_strncat(char *s, const char *ct, int n);

/* compare at most n characters of string cs to string ct; return < 0 
 * if cs < ct, 0 if cs == ct, or > 0 if cs > ct. */
int my_strncmp(const char *cs, const char *ct, int n);

void get_line(char *s, int lim);
void get_string(char *s, int lim);

void main() {
	char s[] = "123596";
	char t[] = "123597";

	printf("%d\n", my_strncmp(s, t, 6));
}

char *my_strncpy(char *s, const char *ct, int n) {
	int i;

	for (i = 0; i < n ; i++) {
		if (*(ct+i) == '\0') {
			*s++ = '\0';
			i++;
			break;
		}
		else
			*s++ = *(ct+i);
	}
	for (; i < n; i++)
		*s++ = '\0';	
	return s - n;
}

char *my_strncat(char *s, const char *ct, int n) {
	int slen, ctlen;

	ctlen = slen = 0;
	while (*s) {
		s++;
		slen++;
	}
	while (ctlen < n)
		*(s+ctlen++) = *ct++;
	*(s+ctlen) = '\0';
	return s - slen;		

}

int my_strncmp(const char *cs, const char *ct, int n) {
	for (; *cs == *ct && n > 1; cs++, ct++, n--)
		if (*cs == '\0')
			return 0;
	return *cs - *ct;	
}

void get_line(char *s, int lim) {
	int i, c;

	i = 0;
	while ((c = getchar()) != EOF && i < lim-1) 
		*(s+i++) = c;
	*(s+i) = '\0';
}

void get_string(char *s, int lim) {
	while ((*s = getchar()) != '\n')
		s++;
	*s = '\0';		
}


