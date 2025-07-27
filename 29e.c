#include <stdio.h>

/* In a two's complement number system, x &= (x-1) deletes 
the rightmost 1-bit in x. Explain why. Use this observation
to write a faster version of bitcount. */

/* It does this because subtracting one from x will modify 
bit pattern by removing the final one bit and possibly adding
more one bits to the right of this removed bit. performing & with
this new bit pattern will ensure all 0's starting at the final 1
bit all the way down to the LSB. */

int bitcountv2(unsigned x);

int main() {

	printf("%d\n", bitcountv2(127));
}

int bitcountv2(unsigned x) {
	int c;
	
	c = 0;
	while (x) {
		x &= x-1;	
		++c;	
	}

	return c;
}
