#include <stdio.h>

void filecopy(FILE *in, FILE *out);
int main(int argc, char *argv[])
{
	FILE *in, *out;

	in = fopen(argv[1], "r");
	out = fopen(argv[2], "w");

	filecopy(in, out);
}

void filecopy(FILE *in, FILE *out)
{
	int c;

	while ((c = getc(in)) != EOF)
		putc(c, out);
}
