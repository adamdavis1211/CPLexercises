#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#define MAXWORD 100
#define NUMFORMS 2
#define TRUE 1
/* Revise minprintf to handle more of the other facilities of printf */

void minprintf(char *fmt, ... );
enum { WIDTH, PRECISION };

int main()
{
	char *s = "testing";
	double test2 = 123.456;			
	int test = 199, test1 = 200;
	minprintf("%5.3d %6.4s %10.2f\n", test, s, test2);
}

/* minprintf: minimal printf with variable argument list */
void minprintf(char *fmt, ...)
{
	va_list ap;
	char *p, buf[MAXWORD];
	int i = 0, width = 0, precision = 0, sl;

	va_start(ap, fmt);
	for (p = fmt; *p; p++) {
		if (*p == '%') {
			if (isdigit(*++p)) {
				for (buf[i++] = *p++; isdigit(buf[i] = *p); i++, p++)
					;
				buf[i] = '\0';
				width = atoi(buf);
				i = 0;
			}
			if (*p == '.') {
				while (isdigit(*++p))
					buf[i++] = *p;
				buf[i] = '\0';
				precision = atoi(buf);
				i = 0;
			}
			if (*p == 'd') {
				sprintf(buf, "%d", va_arg(ap, int));
				if (precision) 
					buf[precision] = '\0';
				sl = strlen(buf);
				printf("%s", buf);
				if ((width -= sl) > 0)
					while (width--)
						putchar('#');
			width = precision = 0;
			} else if (*p == 's') {
				sprintf(buf, "%s", va_arg(ap, char *));
				if (precision) 
					buf[precision] = '\0';
				sl = strlen(buf);
				printf("%s", buf);
				if ((width -= sl) > 0)
					while (width--)
						putchar('#');
			width = precision = 0;
			} else if (*p == 'f') {
				sprintf(buf, "%f", va_arg(ap, double));
				if (precision) {
					while (buf[i++] != '.')
						;
					buf[i+precision] = '\0';
				}
				sl = strlen(buf);
				printf("%s", buf);
				if ((width -= sl) > 0)
					while (width--)
						putchar('#');
			width = precision = 0;
			}
		} else
			putchar(*p);
			
	}
	va_end(ap);
}

