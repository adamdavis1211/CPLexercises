#include <stdio.h>
#include "util.h"
#define MAX 1000

/* write an alternative version of squeeze(s1, s2) that deletes each character
in s1 that matches any character in s2 */

void squeeze_v2(char s1[], char s2[]);

int main() {
	int d;
	char s[MAX];
	char t[] = "1236";

	while ((d = get_line(s, MAX)) > 0) {
		squeeze_v2(s, t);
		printf("%s", s);
	}
}

void squeeze_v2(char s1[], char s2[]) {
	int i, j, k;

	/* while there is a character in s1
		search for match in s2
		if match in s2
			 remove character
		else
			copy char to buffer 
			repeat for next character
	*/
	k = 0;
	for (i = 0; s1[i] != '\0'; ++i)  {
		j = 0;
		while (s1[i] != s2[j] && s2[j] != '\0') 
			j++;
		if (s2[j] == '\0')
			s1[k++] = s1[i];
	}
	s1[k] = '\0';
}

