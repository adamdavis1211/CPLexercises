#include <stdio.h>

#define ISBLANK(c) ((c) == ' ' || (c) == '\t')

main() {
	int c, flag;
	flag = 0;
	for (c = getchar(); c != EOF; c = getchar()) {
		if (ISBLANK(c) && flag == 0) {
			putchar(c);
			flag = 1;
		}
		
		if (ISBLANK(c) && flag == 1) {
			flag = 1;
		}		

		else {
			putchar(c);
			flag = 0;
		}
	}
}
