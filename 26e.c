#include <stdio.h>
#define BITS 32

unsigned int setbits(unsigned x, unsigned p, unsigned n, unsigned y);

/* Write a function setbits(x, p, n, y) that returns x with the n bits that begin at position p set to the rightmost n bits of y, leaving the other bits unchanged. */

int main() {
	printf("%u\n", setbits(204, 7, 2, 0));
}

unsigned int setbits(unsigned x, unsigned p, unsigned n, unsigned y) {
	unsigned int pre, mid, post;
	pre = ~0;
	pre = pre >> (BITS - p - 1);
	pre = (~pre) & x;
	printf("pre: %u\n", pre);

	post = ~0;
	post = post << (p + 1 - n);
	post = (~post) & x;
	printf("post: %u\n", post);

	mid = ~0;
	mid = mid << n;
	mid = ~mid & y;
	mid = mid << (p + 1 - n);
	printf("mid: %u\n", mid);
	return pre | mid | post;
}
