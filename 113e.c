#include <stdio.h>

main() {
	int i, j, c, lc, max;
	int hist[10];
	for (i = 0; i < 10; ++i)
		hist[i] = 0;

	max, lc = 0;
	while ((c = getchar()) != EOF) {
		if (c != ' ' && c != '\t' && c != '\n')
			++lc;
		else if (lc != 0) { 
			++hist[lc];
			if (lc > max)
				max = lc;
			lc = 0;
		}
	}

	for (i = 0; i < 10; ++i)
		printf("%d letter words: %d\n", i, hist[i]);
	printf("max: %d\n", max);	
	
	for (i = 0; i < 10; ++i) {
		printf("%d ", i);
		for (j = 0; j < max; ++j) {
			if (hist[i] > 0) {
				putchar('#');
				--hist[i];
			}
			else {
				putchar(' ');
			}
		}
		putchar('\n');	
	}
}
