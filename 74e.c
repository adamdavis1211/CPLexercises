#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>
#define SPECIFIERS 2
#define SET 1
#define OFF 0
#define MAX 100
/* Write a private version of scanf analogous to minprinf from the
previous section. */

enum { SUPPRESS, WIDTH };

int specifiers[SPECIFIERS];
int myatoi(char s[]);
void minscanf(char *fmt, ...);

int main()
{
	char *s = "%10s%10s";
	char w[MAX], j[MAX];
	int x, y;
	minscanf(s, w, j);
	printf("%s %s\n", w, j);
}

void minscanf(char *fmt, ...)
{
	va_list ap;
	int i = 0;
	char buf[MAX], c, *p;
	int scanned = 0;

	va_start(ap, fmt);
	for (p = fmt; *p; p++) {
		if (*p == '%') {		/* start of conversion specifier */
			p++;
			specifiers[SUPPRESS] = specifiers[WIDTH] = OFF;
			if (*p == '*') {
				specifiers[SUPPRESS] = SET;
				p++;
			}
			if (isdigit(*p)) {
				while (isdigit(buf[i] = *p))
					i++, p++;
				buf[i] = '\0';
				i = OFF;
				specifiers[WIDTH] = myatoi(buf);
			}
			if (*p == 'd') {
				if (specifiers[WIDTH]) {
					while (i < specifiers[WIDTH] && 
					isdigit(buf[i] = getchar()))
						i++;
					ungetc(buf[i], stdin);
					buf[i] = '\0';
					i = OFF;
					if (!specifiers[SUPPRESS]) {
						int *arg = va_arg(ap, int *);
						*arg = myatoi(buf);
					}
				} else {
					while (isdigit(buf[i] = getchar()))
						i++;
					ungetc(buf[i], stdin);
					buf[i] = '\0';
					i = OFF;
					if (!specifiers[SUPPRESS]) {
						int *arg = va_arg(ap, int *);
						*arg = myatoi(buf);
					} 
				}
			} else if (*p == 's') {
				if (specifiers[WIDTH]) {
					while (i < specifiers[WIDTH] && 
					!isblank(buf[i] = getchar()) && !iscntrl(buf[i]))
						i++;
					ungetc(buf[i], stdin);
					buf[i] = '\0';
					i = OFF;
					if (!specifiers[SUPPRESS]) {
						char *arg = va_arg(ap, char *);
						sprintf(arg, "%s", buf);
					}
				}
			}
		}
	}
	va_end(ap);
}

					
int myatoi(char s[]) 
{
	int i, n, sign;

	for (i = 0; isspace(s[i]); i++);	/* skip white space */
	sign = (s[i] == '-') ? -1 : 1;
	if (s[i] == '+' || s[i] == '-')	/* skip sign */
		i++;
	for (n = 0; isdigit(s[i]); i++)
		n = 10 * n + (s[i] - '0');
	return sign * n;
}
						
			
