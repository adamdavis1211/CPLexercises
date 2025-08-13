#include <stdio.h>
#include <string.h>
#define MAXLINE 1000
/* Write a program to compare two files, printing the first line where they differ. */

int main(int argc, char *argv[])
{
	int lineno = 1;
	FILE *fp1, *fp2;
	char *f1, *f2, line1[MAXLINE], line2[MAXLINE];

	if (argc != 3) {
		printf("Usage: ./go filepath1 filepath2\n");
		return -1;
	}

	fp1 = fopen(argv[1], "r");
	fp2 = fopen(argv[2], "r");

	while ((f1 = fgets(line1, MAXLINE, fp1)) != NULL && 
		(f2 = fgets(line2, MAXLINE, fp2)) != NULL) {
		if (strcmp(line1, line2)) {
			printf("line %d, %s: %s\n", lineno, argv[1], line1);
			printf("line %d, %s: %s\n", lineno, argv[2], line2);
			return 0;
		}
		lineno++;
	}
	printf("EOF reached in file: %s\n", (f1 == NULL) ? argv[1] : argv[2]);
}
