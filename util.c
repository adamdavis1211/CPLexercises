#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include "util.h"

/* squeeze: delete all c from s */
void squeeze(char s[], int c) {
	int i, j;

	for (i = j = 0; s[i] != '\0'; i++)
		if (s[i] != c)
			s[j++] = s[i];
	s[j] = '\0';
}

int get_line(char s[], int lim) {
        int c, i;

        for (i = 0; i < lim-1 && (c = getchar()) != EOF && c != '\n'; ++i)
                s[i] = c;
        if (c == '\n') {
                s[i] = c;
                ++i;
        }
        s[i] = '\0';
        return i;
}

/* str_cat: concatenate t to the end of s; s must be big enough */
void str_cat(char s[], char t[]) {
	int i, j;

	i = j = 0;
	while (s[i] != '\n') 	/* find end of s */
		i++;
	while ((s[i++] = t[j++]) != '\0');	/* copt t */
}


/* bitcount: return the number of 1 bits in the integer argument */

int bitcount(unsigned x) {
	int b;
	
	for (b = 0; x != 0; x >>= 1) 
		if (x & 01) 
			b++;
	return b;
}


/* (31e.c) binsearch: find x in v[0] <= v[1] <= ... <= v[n-1] */
int my_binsearch(int x, int v[], int n) {
	int low, high, mid, ind;

	low = 0;
	high = n - 1;
	while (v[mid = (low+high)/2] != x && low <= high) {
		(x < v[mid]) ? (high = mid - 1) : (low = mid + 1);
	}
	(v[mid] == x) ? ind = mid : (ind = -1);
	return ind; 	/* no match */
}


int binsearch(int x, int v[], int n) {
	int low, high, mid;
	
	low = 0;
	high = n - 1;
	while (low <= high) {
		mid = (low+high) / 2;
		if (x < v[mid])
			high = mid - 1;
		else if (x > v[mid])
			low = mid + 1;
		else
			return mid;
	}
	return -1;
}

/* count digits, white space, others */
void numwhite() {
	int c, i, nwhite, nother, ndigit[10];

	nwhite = nother = 0;
	for (i = 0; i < 10; i++)
		ndigit[i] = 0;
	while ((c = getchar()) != EOF) {
		switch (c) {
			case '0': case '1': case '2': case '3': case '4':
			case '5': case '6': case '7': case '8': case '9':
				ndigit[c-'0']++;
				break;
			case ' ':
			case '\n':
			case '\t':
				nwhite++;
				break;
			default: 
				nother++;
				break;
			}
		}
		printf("digits =");
		for (i = 0; i < 10; i++)
			printf(" %d", ndigit[i]);
		printf(", white space = %d, other = %d\n", nwhite, nother);
}


/* (32e.c) escape: write a function that converts characters like newline 
and tab into visible escape sequences like \n and \t as it copies the 
string t to s. */

int escape(char s[], char t[], int maxlen) {
	int i, j;

	for (i = j = 0; s[i] != '\0' && j < maxlen - 2; i++, j++) {
		switch (s[i]) {
			case '\t': case '\n':
				t[j++] = '\\';
				t[j] = (s[i] == '\t') ? 't' : 'n';	
				break; 
			default: 
				t[j] = s[i];
				break;
		}
	}
	if (j == maxlen - 2) s[j] = '\0';
	return j;
}
		

void unescape(char s[], char t[], int maxlen) {
	int i, j;

	for (i = j = 0; j < maxlen-2 && s[i] != '\0'; i++, j++) {
		switch (s[i]) {
			case '\\':
				if (s[i+1] == 'n') {
					t[j] = '\n';
					i++;	
				}
				else if (s[i+1] == 't') {
					t[j] = '\t';
					i++;
				}
				else
					t[j] = '\\';	
				break;
			default:
				t[j] = s[i];	
				break;
		}
	}
	t[j] = '\0';
}	


/* atoiv2: convert s to integer; version 2 */

int myatoi( char s[]) {
	int i, n, sign;

	for (i = 0; isspace(s[i]); i++);	/* skip white space */
	sign = (s[i] == '-') ? -1 : 1;
	if (s[i] == '+' || s[i] == '-')	/* skip sign */
		i++;
	for (n = 0; isdigit(s[i]); i++)
		n = 10 * n + (s[i] - '0');
	return sign * n;
}


/* shellsort: sort v[0] ... v[n-1] into increasing order */
void shellsort(int v[], int n) {
	int gap, i, j, temp;

	for (gap = n/2; gap > 0; gap /= 2)
		for (i = gap; i < n; i++)
			for (j=i-gap; j>= 0 && v[j]>v[j+gap]; j-=gap) {
				temp = v[j];
				v[j] = v[j+gap];
				v[j+gap] = temp;
			}
}


/* reverse: reverse string s in place */ 

void reverse(char s[]) {
	int c, i, j;

	for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

/* (33e.c) */
void expand(char s1[], char s2[]) {
	int i, j, k, first, second, fchar, schar, lock;

	/* get the first shorthand interval. the end of the short hand is 
	two back to back chars or a null. if a '-' is last char before
	null, disregard it. */

	i = j = k = lock = 0;
	fchar = schar = 1;
	while (s1[i] != '\0') {
		switch (s1[i]) {
			case '-': 	/* should disregard first one */
				if (lock && s1[i+1] != '\0') 
					lock = 0, schar = 1;
				break;
			case '\n':
				break;
			default:	
				lock = 0;
				if (fchar) 
					first = s1[i],	fchar = 0;
				else if (schar) {
					second = s1[i],	schar = 0;
					if (s1[i+1] == '-')
						lock = 1;
				}
				break;
		}
		if (!fchar && !schar && !lock) {
			for (k = first; k <= second; k++)
				s2[j++] = k;
			fchar = schar = 1;
		}
		i++;
	
	}	
	s2[j] = '\0';
	printf("%s", s2);
}


/* itoa: convert n to characters in s */
void itoa(int n, char s[]) {
	int i, sign; 
	unsigned num;

	num = ((sign = n) < 0) ? -n : n;
	i = 0;
	do 
		s[i++] = num % 10 + '0';
	while ((num /= 10) > 0);
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);				/* generate digits in reverse order */	
}


/* (35e.c) itob(n, s, b) */

void itob(int n, char s[], int b) {
	int i, sign;
	unsigned num;

	num = ((sign = n) < 0) ? -n : n;
	i = 0;
	do {
		if ((num % b) > 9)
			s[i++] = num % b + '7';
		else
			s[i++] = num % b + '0';
	} while ((num /= b) > 0);
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
}

/* trim: remove trailing blanks, tabs, newlines */
int trim(char s[]) {
	int n;
	for (n = strlen(s)-1; n >= 0; n--)
		if (s[n] != ' ' && s[n] != '\t' && s[n] != '\n')
			break;
	s[n+1] = '\0';
	return n; 
	
}

/* my_atof: convert string s to double */

double my_atof(char s[]) {
	double val, power, temp;
	int i, sign, esign;
	
	for (i = 0; isspace(s[i]); i++);	/* skip white space  */
	sign = (s[i] == '-') ? -1 : 1;
	if (s[i] == '+' || s[i] == '-') i++;
	for (val = 0; isdigit(s[i]); i++)
		val = 10.0 * val + (s[i] - '0');
	if (s[i] == '.') i++;
	for (power = 1.0; isdigit(s[i]); i++) {
		val = 10.0 * val + (s[i] - '0');
		power *= 10;
	}
	temp = sign * val / power;	
	if (s[i] == 'e' || s[i] == 'E') i++;
	esign = (s[i] == '-') ? -1 : 1;
	if (s[i] == '+' || s[i] == '-') i++;
	for (val = 0; isdigit(s[i]); i++)
		val = 10 * val + (s[i] - '0');
	return temp * pow(10, (val * esign));		
}

#include "alloc.h"
#define MAXLEN 1000
int readlines(char *lineptr[], int maxlines) 
{
	int len, nlines;
	char *p, line[MAXLEN]; 
	
	nlines = 0;
	while ((len = get_line(line, MAXLEN)) > 0) {
		if (nlines >= maxlines || (p = alloc(len)) == NULL)
			return -1;
		else {
			line[len-1] = '\0';
			strcpy(p, line);
			lineptr[nlines++] = p;
		}
	}
	return nlines;
}

void writelines(char *lineptr[], int nlines) 
{
	while (nlines-- > 0) 
		printf("%s\n", *lineptr++);
}

/* r_writelines:   write lines of array in reverse order */
void r_writelines(char *lineptr[], int nlines)
{
	lineptr += nlines-1;
	
	while (nlines-- > 0) 
		printf("%s\n", *lineptr--);
}

void swap(void *v[], int i, int j)
{
	void *temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

int f_strcmp(const char *s1, const char *s2)
{
	for (; tolower(*s1) == tolower(*s2); s1++, s2++)
		if (*s1 == '\0')
			return 0;
	return tolower(*s1) - tolower(*s2);
} 

int fd_strcmp(const char *s, const char *t)
{
	do {
		while (ispunct(*s))
			s++;
		while (ispunct(*t))
			t++;
		if (*s == '\0' || *t == '\0')
			break;
	} while (tolower(*s) == tolower(*t));
	
	return tolower(*s) - tolower(*t);
}

int d_strcmp(const char *s, const char *t)
{
	do {
		while (ispunct(*s))
			s++;
		while (ispunct(*t))
			t++;
		if (*s == '\0' || *t == '\0')
			break;
	} while ((*s) == (*t));
	
	return (*s) - (*t);
}


/* numcmp:  compare s1 and s2 numerically */
int numcmp(const char *s1, const char *s2)
{
	double v1, v2;

	v1 = atof(s1);
	v2 = atof(s2);
	if (v1 < v2)
		return -1;
	else if (v1 > v2)
		return 1;
	else
		return 0;
}

#define MAXWORD 20

int w_numcmp(const char *s, const char *t, int field)
{
	double v1, v2;
	int fieldno = 0, i = 0;
	char sarr[MAXWORD], tarr[MAXWORD];
	
	while (*s) { 
		if (*s == ' ' || *s == '\t') {
			while (*++s == ' ' || *s == '\t')
				;
			if (++fieldno == field) {
				while (*s != ' ' && *s != '\t' && i < MAXWORD) {
					sarr[i++] = *s++;
					if (*s == '\0')
						break;
				}
				sarr[i] = '\0';
				break;
			}
		} else 
			s++;
	}
	
	fieldno = i = 0;	
	while (*t) { 
		if (*t == ' ' || *t == '\t') {
			while (*++t == ' ' || *t == '\t')
				;
			if (++fieldno == field) {
				while (*t != ' ' && *t != '\t' && i < MAXWORD) {
					tarr[i++] = *t++;
					if (*t == '\0')
						break;
				}
				tarr[i] = '\0';
				break;
			}
		} else 
			t++;
	}
	v1 = atof(sarr);
	v2 = atof(tarr);
	if (v1 < v2)
		return -1;
	else if (v1 > v2)
		return 1;
	else
		return 0;	
}

int w_strcmp(const char *s, const char *t, int field)
{
	int fieldno = 0;

	while (*s) { 
		if (*s == ' ' || *s == '\t') {
			while (*++s == ' ' || *s == '\t')
				;
			if (++fieldno == field)
				break;
		} else 
			s++;
	}
	
	fieldno = 0;	
	while (*t) { 
		if (*t == ' ' || *t == '\t') {
			while (*++t == ' ' || *t == '\t')
				;
			if (++fieldno == field)
				break;
		} else 
			t++;
	}

	for (; *s == *t; s++, t++)
		if (*s == '\0' || *s == ' ' || *s == '\t')
			return 0;
	return *s - *t;
}
