#include <stdio.h>

main() {
	float fahr, celsius;
	float lower, upper, step;
	
	lower = 0;
	upper = 15;
	step = 1;

	celsius = lower;
	while (celsius <= upper) {
		fahr = (9.0/5.0) * celsius + 32.0;
		printf("%.0f %3.1f\n", celsius, fahr);
		celsius += step;
	}
}	
