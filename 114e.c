#include <stdio.h>

main() {
	int c, i, j;
	int alpha[128];

	for (i = 0; i < 128; ++i)
		alpha[i] = 0;
	
	while ((c = getchar()) != EOF) 
		++alpha[c];

	for (i = 0; i < 128; ++i) {
		printf("%d %c  ", i, i);
		for (j = alpha[i]; j > 0; --j) {
			putchar('#');
		}
		putchar('\n');	
	}	
}	
