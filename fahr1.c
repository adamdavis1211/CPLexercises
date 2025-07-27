#include <stdio.h>
	
	/* print Fahrenheit-Celsius table
	   for fahr = 0, 20, ..., 300 */
	
main() {
	float fahr, celsius;
	float lower, upper, step;

	lower = 0;	/* lower limit of temp scale */	
	upper = 300;	/* upper limit */
	step = 20;	/* step size */

	fahr = lower;
	printf("%s %s\n", "Fahrenheight", "Celsius");
	while (fahr <= upper) {
		celsius = (5.0/9.0) * (fahr - 32.0);	/* integer division truncates in C
							   so 5/9 would truncate to 0 */	   
		printf("%6.0f% 13.1f\n", fahr, celsius);
		fahr += step;
	}
}
