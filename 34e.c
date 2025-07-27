#include <stdio.h>
#include "util.c"
#include "limits.h"
#define MAX 1000

int main() {
	char s[MAX]; 
	int n;

	n = INT_MIN;
	printf("min: %d\n", n);
	itoa(n, s);
	printf("%s\n", s);
}
