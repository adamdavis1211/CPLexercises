#include "util.c"

/* Out binary search makes two tests inside the loop, when
one would suffice (at the price of more tests outside.) 
Write a version with only one test inside the loop and 
measure the difference in run-time. */

int main() {
	int arr[10];
	int i;

	for (i = 0; i < 10; ++i) 
		arr[i] = i;

	printf("%d\n", binsearch(7, arr, 10));
}
