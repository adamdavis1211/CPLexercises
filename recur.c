#include <stdio.h>

void printd(int);

main() {
	int i;
	int arr[] = { 8, 5, 2, 4, 1, 3, 7, 6 };

	quicksort(arr, 0, 7);
	for (i = 0; i < 7; i++)
		printf("%d, ", arr[i]);
	printf("%d.\n", arr[i]);
}

/* printd: print n in decimal */
void printd(int n) {
	if (n < 0) {
		putchar('-');
		n = -n;
	}
	if (n / 10) 
		printd(n / 10);
	putchar(n % 10 + '0');
}	

/* qsort: sort v[left]...v[right] into increasing order */
void quicksort(int v[], int left, int right) {
	int i, last;
	void swap(int v[], int i, int j);

	if (left >= right)	/* do nothing if array contains */
		return;		/* fewer than two elements */
	swap(v, left, (left + right)/2);	/* move partition elem */	
	last = left;				/* to v[0] */
	for (i = left + 1; i <= right; i++)		/* partition */
		if (v[i] < v[left])
			swap(v, ++last, i);
	swap(v, left, last);		/* restore partition elem */
	quicksort(v, left, last-1);
	quicksort(v, last+1, right);
}

/* swap: interchange v[i] and v[j] */
void swap(int v[], int i, int j) {
	int temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}
