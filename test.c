#include <stdio.h>
#include "util.c"

int main() {
	int i;
	int arr[5] = {4,3,5,1,2};

	shellsort(arr, 5);
	for (i = 0; i < 5; i++)
		printf("%d ", arr[i]);
	putchar('\n');



}
