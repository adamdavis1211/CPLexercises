#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

/* Add a field-searching capability, so sorting may be done on fields within
lines, each field sorted according to an independent set of options. (The
index for this book was sorted with -df for the index category and -n for the
page number.) */

#define MAXLINES 5000		/* max lines to be sorted */
char *lineptr[MAXLINES];	/* pointers to text lines */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void r_writelines(char *lineptr[], int nlines);

void q_sort(void *lineptr[], int left, int right, int (*comp)(void *,void *));
int numcmp(char *, char *);
int f_strcmp(const char *, const char *);
int d_strcmp(const char *, const char *);
int fd_strcmp(const char *, const char *);
int w_strcmp(const char *s, const char *t, int field);
int w_numcmp(const char *s, const char *t, int field);
void wq_sort(void *lineptr[], int left, int right, int field, int (*comp)(void *, void *, int));


/* sort input lines */
int main(int argc, char *argv[]) 
{
	int nlines;		/* number of input lines read */
	int numeric = 0;	/* 1 if numeric sort */
	int reverse = 0;	/* 1 if reverse sort */
	int fold = 0;		/* 1 if non case sensitive comparison */ 
	int directory = 0; 	/* compare only letters, numbers, and blanks */
	int field, fieldno = 0;
	char *t, *s;

	for (argc -= 1; argc > 0; argc--) {
		if (strcmp(argv[argc], "-n") == 0)
			numeric = 1;
		else if (strcmp(argv[argc], "-r") == 0)
			reverse = 1;
		else if (strcmp(argv[argc], "-f") == 0)
			fold = 1;
		else if (strcmp(argv[argc], "-d") == 0)
			directory = 1;	
		else if ( *(t = argv[argc]) == '-' && *++t == 'w') {
			s = t+1;
			while (*++t)
				if (!isdigit(*t)) {
					printf("Usage: sort -w (w must be integral value)\n");
						return -1;
				}
			field = 1, fieldno = atoi(s);
			printf("%d\n", fieldno);
		}
		else {
			printf("Usage: sort -n (numeric) -r (reverse)\n");
			return -1;
		}
	}
 
	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		if (fold)
			if (directory)
				if (field)
					return -1;
				else    
					q_sort((void**) lineptr, 0, nlines-1,
					(int (*)(void *, void *))(numeric ? numcmp : fd_strcmp));
			else
				q_sort((void**) lineptr, 0, nlines-1,
				(int (*)(void *, void *)) (numeric ? numcmp : f_strcmp));
		else if (directory)
			q_sort((void**) lineptr, 0, nlines-1,
			(int (*)(void *, void *)) (numeric ? numcmp : d_strcmp));
		else if (field)
			wq_sort((void**) lineptr, 0, nlines-1, fieldno,
			(int (*)(void *, void *, int))(numeric ? w_numcmp : w_strcmp));
		else
			q_sort((void**) lineptr, 0, nlines-1,
			(int (*)(void *, void *)) (numeric ? numcmp : strcmp));
		(reverse ? r_writelines : writelines)(lineptr, nlines);
		return 0;
	} else {
		printf("input too big to sort\n");
		return 1;
	}
}

/* q_sort:  sort v[left]...v[right] into increasing order */
void q_sort(void *v[], int left, int right,
		int (*comp) (void *, void *))
{
	int i, last;
	
	void swap(void *v[], int, int);
	
	if (left >= right)
		return;
	swap(v, left, (left + right)/2);
	last = left;
	for (i = left+1; i <= right; i++)
		if ((*comp) (v[i], v[left]) < 0)
			swap(v, ++last, i);
	swap(v, left, last);
	q_sort(v, left, last-1, comp);
	q_sort(v, last+1, right, comp);
}

void wq_sort(void *v[], int left, int right, int fieldno,
		int (*comp) (void *, void *, int))
{
	int i, last;
	
	void swap(void *v[], int, int);
	
	if (left >= right)
		return;
	swap(v, left, (left + right)/2);
	last = left;
	for (i = left+1; i <= right; i++)
		if ((*comp) (v[i], v[left], fieldno) < 0)
			swap(v, ++last, i);
	swap(v, left, last);
	wq_sort(v, left, last-1, fieldno, comp);
	wq_sort(v, last+1, right, fieldno, comp);
}


