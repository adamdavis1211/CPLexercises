#include <stdio.h>
#include <unistd.h>
#define BUFSIZE 100

int main() 
{
	return 0;
}

/* getchar:  unbuffered single character input */
int my_getcharv1(void)
{
	char c;

	return (read(0, &c, 1) == 1) ? (unsigned char) c : EOF;
}

/* getchar: simplified buffered version */
int my_getcharv2(void)
{
	static char buf[BUFSIZE];
	static char *bufp = buf;
	static int n = 0;

	if (n == 0) {
		n = read(0, buf, sizeof buf);
		bufp = buf;
	}
	return (--n >= 0) ? (unsigned char) *bufp++ : EOF;
}

long lseek(int fd, long offset, int origin);

/* get:  read n bytes from position pos */
int get(inf fd, long ps, char *buf, int n)
{
	if (lseek(fd, pos, 0) >= 0)	/* get to pos */
		return read(fd, buf, n);
	else
		return -1;
}
