#include <stdio.h>
#include <string.h>

/* Modify the sort program to handle a -r flag, which indicates sorting in 
reverse (decreasing) order. Be sure that -r works with -n. */

#define MAXLINES 5000		/* max lines to be sorted */
char *lineptr[MAXLINES];	/* pointers to text lines */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void r_writelines(char *lineptr[], int nlines);

void q_sort(void *lineptr[], int left, int right, int (*comp)(void *,void *));
int numcmp(char *, char *);

/* sort input lines */
int main(int argc, char *argv[]) 
{
	int nlines;		/* number of input lines read */
	int numeric = 0,  reverse = 0;	/* 1 if numeric sort, 1 if reverse sort*/

	for (argc -= 1; argc > 0; argc--) {
		if (strcmp(argv[argc], "-n") == 0)
			numeric = 1;
		else if (strcmp(argv[argc], "-r") == 0)
			reverse = 1;
		else {
			printf("Usage: sort -n (numeric) -r (reverse)\n");
			return -1;
		}
	}
 
	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		q_sort((void**) lineptr, 0, nlines-1,
			(int (*)(void *,void *)) (numeric ? numcmp : strcmp));
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

