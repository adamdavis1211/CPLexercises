#include <stdio.h>

unsigned invert(unsigned x, int p, int n);

/* write a function invert(x, p, n) that returns x with the n bits
that begin at position p inverted while leaving the others unchanged. */

int main() {
	unsigned short k;
	int i;

	k = 1;	
	for (i = 0; i < sizeof(short) * 8; ++i) {
		k = k << 1; 
		printf("%u\n", k);
	}
}

unsigned invert(unsigned x, int p, int n) {
	int j; 

	j = ~0;
	j = j << n;
	j = ~j;
	j = j << (p - n + 1);	
	return j ^ x;
}
