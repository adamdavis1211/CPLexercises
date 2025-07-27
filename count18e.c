#include <stdio.h>

main() {
	int c, count;
	count = 0;
	
	for (c = getchar(); c != EOF; c = getchar())
		if (c == '\n' || c == '\t' || c == ' ')
			count++; 
	printf("%d\n", count);
}
