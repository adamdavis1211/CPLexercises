/* Rewrite fopen and _fillbuf with fields instead of explicit bit operations, 
Compare code size and execution speed. */

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "82e.h"
#define PERMS 0666	/* RW for owner, group, and others */

FILE _iob[OPEN_MAX] = {
	{ 0, (char *) 0, (char *) 0, 0, 1 },
	{ 0, (char *) 0, (char *) 0, 1, 0, 1 },
	{ 0, (char *) 0, (char *) 0, 2, 0, 1, 0, 1 }
};

int main()
{

}

FILE *fopen(char *name, char *mode)
{
	int fd;
	FILE *fp;

	if (*mode != 'r' && *mode != 'w' && *mode != 'a')
		return NULL;
	for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
		if (!fp->read && !fp->write )
			break;		/* found free slot */
	if (fp >= _iob + OPEN_MAX)	/* no free slots */
		return NULL;
	if (*mode == 'w')
		fd = creat(name, PERMS);
	else if (*mode == 'a') {
		if ((fd = open(name, O_WRONLY, 0)) == -1)
			fd = creat(name, PERMS);
		lseek(fd, 0L, 2);
	} else
		fd = open(name, O_RDONLY, 0);
	if (fd == -1)
		return NULL;
	fp->fd = fd;
	fp->cnt = 0;
	fp->base = NULL;
	if (*mode == 'r')
		fp->read = 1;
	else
		fp->write = 1;
	return fp;
}

/* _fillbuf:  allocate and fill input buffer */
int _fillbuf(FILE *fp)
{
	int bufsize;
	
	if (!fp->read || fp->eof || fp->err)
		return EOF;
	bufsize = (fp->unbuf) ? 1 : BUFSIZ;
	if (fp->base == NULL)	/* no buffer yet */
		if ((fp->base = (char *) malloc(bufsize)) == NULL)
			return EOF;	/* can't get buffer */
	fp->ptr = fp->base;
	fp->cnt = read(fp->fd, fp->ptr, bufsize);
	if (--fp->cnt < 0) {
		if (fp->cnt == -1)
			fp->eof = 1;
		else
			fp->err = 1;
		fp->cnt = 0;
		return EOF;
	}
	return (unsigned char) *fp->ptr++;
}
