#include <stdio.h>
#include <string.h>

/* Add the option -f to fold upper and lower case together, so that case
distinctions are not made during sorting; for example, a and A compare
equal. */  

#define MAXLINES 5000		/* max lines to be sorted */
char *lineptr[MAXLINES];	/* pointers to text lines */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void r_writelines(char *lineptr[], int nlines);

void q_sort(void *lineptr[], int left, int right, int (*comp)(void *,void *));
int numcmp(char *, char *);
int f_strcmp(const char *, const char *);

/* sort input lines */
int main(int argc, char *argv[]) 
{
	int nlines;		/* number of input lines read */
	int numeric = 0;	/* 1 if numeric sort */
	int reverse = 0;	/* 1 if reverse sort */
	int fold = 0;	 	/* 1 if non case sensitive comparison */
	int directory = 0; 	/* compare only letters, numbers, and blanks. */

	for (argc -= 1; argc > 0; argc--) {
		if (strcmp(argv[argc], "-n") == 0)
			numeric = 1;
		else if (strcmp(argv[argc], "-r") == 0)
			reverse = 1;
		else if (strcmp(argv[argc], "-f") == 0)
			fold = 1;
		else if (strcmp(argv[argc], "-d") == 0)
			directory = 1;
		else {
			printf("Usage: sort -n (numeric) -r (reverse)\n");
			return -1;
		}
	}
 
	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		if (fold)
			q_sort((void**) lineptr, 0, nlines-1,
			(int (*)(void *, void *)) (numeric ? numcmp : f_strcmp));
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

