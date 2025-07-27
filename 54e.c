#include <stdio.h>

/* 5e.c:  Write the function strend(s,t), which returns 1 if the string t 
 * occurs at the end of string s, and zero otherwise */

int strend(char *, char *); 

int main() {
	int v;
	char *s = "21";
	char *t = "1";

	v = strend(s, t);
	printf("%s\n", (v == 1) ? "true" : "false");
}

int strend(char *s, char *t) {
	int tlen, slen, diff;

	slen = tlen = 0;
	while (*(t + tlen))
		tlen++;
	while (*(s + slen))
		slen++;
	if ((diff = slen - tlen) < 0) 
		return 0;
	else {
       		s += diff;		
		while (*t++ == *s++)
			if (*t == '\0')
				return 1;
		return 0;
	}		

}
