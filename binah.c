#include <stdio.h> 
#include "util.h"

unsigned int getbits(unsigned int x, int p, int n);

int main() {
	int x, p, n;

	x = 218;
	p = 5;
	n = 3;
	printf("%d\n", getbits(x, p, n));
}

/* getbits: get n bits from position p */
unsigned int getbits(unsigned int x, int p, int n) {
	return (x >> (p+1-n)) & ~(~0 << n);
}


