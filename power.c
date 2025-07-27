#include <stdio.h>

/* test the power function */

int power(int base, int n);

main() {
	int i;

	for (i = 0; i < 10; ++i)
		printf("%d %d %d\n", i, power(2, i), power(-3, i));
	return 0;
}

/* compute and return base raised to the power n */

int power(int base, int n) {
	int i, p;

	p = 1;
	for (i = 1; i <= n; ++i)
		p *= base;
	return p;
}
	 
