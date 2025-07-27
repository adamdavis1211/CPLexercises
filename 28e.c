#include <stdio.h>
#define BITS 32

unsigned rightrot(unsigned x, int n);

/* Write a function rightrot(x, n) that returns the value of the integer
x rotated to the right by n positions */ 

int main() {
	printf("%u\n", rightrot(240, 5));
}

unsigned rightrot(unsigned x, int n) {
	int s, i, ind;
	unsigned j, tmp;

	s = n % BITS;
	tmp = x >> s;	
	j = ~(~0 << s) & x;
	for (i = ind = 0; i < BITS; ++i) 
		if ((1 << i) & tmp)
			ind = i+1;
	j = j << (ind);
	return tmp | j;

}
