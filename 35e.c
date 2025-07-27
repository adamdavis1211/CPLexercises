#include "util.c"
#include <stdio.h>
#define MAX 1000

int main() {
	char s[MAX];
	int n;

	n = 1000;
	itob(n, s, 16);
	printf("%s\n", s);
}
