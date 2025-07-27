#include <stdio.h>

void to_lower();

/* Rewrite the function lower, which converts upper case letters
to lower case, with a conditional expression instead of if-else */

int main () {
	to_lower();
	return 1;	
}

void to_lower() {
	int c;	
	
	while ((c = getchar()) != EOF) 
		putchar((c >= 'A' && c <= 'Z') ? c + 32 : c);
}


