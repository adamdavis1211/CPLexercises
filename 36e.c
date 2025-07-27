#include <stdio.h>
#include <stdlib.h>
#include "util.c"
#define NUMS 5
#define MAX 1000

void newitoa(int n, char s[], int w);

/* (36e.c_) 
	Write a version of itoa that accepts three agruments instead of two. The
third argument is a minimum field width; the converted number must be padded with
blanks on the left in necessary to make it wide enough. */

int main() {
	int i, numbers[NUMS];	
	char str[MAX];
	
	for (i = 0; i < 5; i++) {
		numbers[i] = i * i;
		newitoa(numbers[i], str, 16);
		printf("%s\n", str);
	}
}

void newitoa(int n, char s[], int w) {
	int i, sign;
	unsigned num;

	num = ((sign = n) < 0) ? -n : n;
	i = 0;	
	do 
		s[i++] = num % 10 + '0';
	while ((num /= 10) > 0);	
	if (sign < 0) 
		s[i++] = '-';
	while (i < w)
		s[i++] = ' ';
	s[i] = '\0';
	reverse(s);
}
