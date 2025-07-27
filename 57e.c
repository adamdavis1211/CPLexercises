#include <stdio.h>
#include <string.h>

#define MAXLINES 5000	/* max #lines to be sorted */
#define MAXBYTES 10000

/* Rewrite readlines to store lines in an array supplied by main, rather
 * than calling alloc to maintain storage. How much faster is the program? 
 */ 

/* psuedo code:
 * 	1. read all the lines of input.
 * 	2. sort them.
 * 	3. print them in order. */ 

char *lineptr[MAXLINES];	/* pointers to text lines */

int readlines(char *lineptr[], int nlines, char *storage, char *p);
void writelines(char *lineptr[], int nlines);

void qsort(char *lineptr[], int left, int right);

/* sort input lines */
int main() {
	int nlines;	/* number of input lines read */
	static char storage[MAXBYTES];
	static char *p = storage;

	if ((nlines = readlines(lineptr, MAXLINES, storage, p)) >= 0) {
		qsort(lineptr, 0, nlines-1);
		writelines(lineptr, nlines);
		return 0;
	} else {
		printf("error: input is too big to sort\n");
		return 1;
	}
}

#include "alloc.h"
#define MAXLEN 1000	/* max length of any input */
int get_line(char *, int);
char *alloc(int);

/* readlines:  read input lines */
int readlines(char *lineptr[], int maxlines, char *storage, char *p) {
	int len, nlines;
	char line[MAXLEN];

	nlines = 0;
	while ((len = get_line(line, MAXLEN)) > 0) {
		if (nlines >= maxlines || storage + MAXBYTES - p < len) 
			return -1;
		else {
			line[len-1] = '\0'; 	/* delete newline */	
			strcpy(p, line);
			lineptr[nlines++] = p;
			p += len;
		}
	}
	return nlines;
}
	
/* writelines:  write output lines */
void writelines(char *lineptr[], int nlines) {
	while (nlines-- > 0 )
		printf("%s\n", *lineptr++);
}

int get_line(char s[], int lim) {
	int c, i;

	for (i = 0; i < lim-1 && (c=getchar()) != EOF && c != '\n'; i++)
		s[i] = c;
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}

void swap(char *v[], int i, int j);

/* qsort:  sort v[left]...v[right] into increasing order */
void qsort(char *v[], int left, int right) {
	int i, last;

	if (left >= right)
		return;
	swap(v, left, (left+right)/2);
	last = left;
	for (i = left+1; i <= right; i++) 
		if (strcmp(v[i], v[left]) < 0)
			swap(v, ++last, i);
	swap(v, left, last);
	qsort(v, left, last-1);
	qsort(v, last+1, right);
}

/* swap:  interchange v[i] and v[j] */
void swap(char *v[], int i, int j) {
	char *temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}
