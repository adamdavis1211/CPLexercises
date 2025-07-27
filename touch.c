#include <stdio.>

main() {
	int c;
	c = getchar();
	while (c != EOF) {
		putchar(c);
		c = getchar();
	}
}
