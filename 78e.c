/* Write a program to print a set of files, starting each new one on a new page,
with a title and a running page count for each file */
#include <stdio.h>
#include <stdlib.h>
#define NAME 1
#define PAGELINES 60

void pfile(char *, char *);

int main(int argc, char *argv[])
{
	int i;

	for (i = NAME; i < argc; i++) {
		printf("%s\n", argv[i]);
		pfile(argv[i], argv[0]);
		putchar('\f');
	}
}

void pfile(char *fname, char *prog)
{
	FILE *fp;
	int c, lineno = 1, page = 1;

	if ((fp = fopen(fname, "r")) == NULL) {
		fprintf(stderr, "%s: can't open %s\n", prog, fname);
		exit(1);
	} else
		while ((c = fgetc(fp)) != EOF) {
			fputc(c, stdout);
			if (c == '\n')
				lineno++;
			if (lineno > PAGELINES) {
				lineno = 1;
				printf("page %d\f", page++);
			}
		}
	printf("page %d\f", page);
	fclose(fp);
}
