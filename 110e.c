#include <stdio.h>

#define TAB '\t'
#define BACKSPACE '\b'
#define BACKSLASH '\\'


main() {
	int c;
	for (c = getchar(); c != EOF; c = getchar()) {
		if (c == TAB) {
			printf("\\t");	
		}
		if (c == BACKSPACE) {
			printf("\\b");
		}
		if (c == BACKSLASH) {
			printf("\\\\");
		} 
		if (c != BACKSLASH && c!= TAB && c!= BACKSPACE) 
			putchar(c);
	}
}

