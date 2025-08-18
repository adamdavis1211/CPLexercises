/* Design and write _flushbuf, fflush, and fclose */

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "sampleh.h"
#define PERMS 0666	/* RW for owner, group, and others */

FILE _iob[OPEN_MAX] = {
	{ 0, (char *) 0, (char *) 0, _READ, 0 },
	{ 0, (char *) 0, (char *) 0, _WRITE, 1 },
	{ 0, (char *) 0, (char *) 0, _WRITE | _UNBUF, 2 }
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
		if ((fp->flag & (_READ | _WRITE)) == 0)
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
	fp->flag = (*mode == 'r') ? _READ : _WRITE;
	return fp;
}

/* _fillbuf:  allocate and fill input buffer */
int _fillbuf(FILE *fp)
{
	int bufsize;

	if ((fp->flag & (_READ | _EOF | _ERR)) != _READ)
		return EOF;
	bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
	if (fp->base == NULL)	/* no buffer yet */
		if ((fp->base = (char *) malloc(bufsize)) == NULL)
			return EOF;	/* can't get buffer */
	fp->ptr = fp->base;
	fp->cnt = read(fp->fd, fp->ptr, bufsize);
	if (--fp->cnt < 0) {
		if (fp->cnt == -1)
			fp->flag |= _EOF;
		else
			fp->flag |= _ERR;
		fp->cnt = 0;
		return EOF;
	}
	return (unsigned char) *fp->ptr++;
}

/* _flushbuf:  clear the input buffer */
int _flushbuf(char c, FILE *fp)
{
	int bufsize, used;

	if ((fp->flag & (_WRITE | _EOF | _ERR)) != _WRITE)
		return EOF;
	bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
	if (fp->flag & _UNBUF) {
		write(fp->fd, &c, 1);
		return c;
	}
	if (fp->base == NULL) {
		if ((fp->base = (char *) malloc(bufsize)) == NULL)
			return EOF;
		fp->ptr = fp->base;
	} 
	used = fp->ptr - fp->base;
	write(fp->fd, fp->base, used);
	fp->ptr = fp->base;
	*fp->ptr++ = c;
	fp->cnt = bufsize-1;
	return c;
}

/* _fflush: clear the input buffer */
int fflush(FILE *fp)
{
	int used, bufsize;

	if ((fp->flag & (_WRITE | _EOF | _ERR)) != _WRITE)
		return EOF;
	used = fp->ptr - fp->base;
	bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
	if (bufsize == 1)
		return 0;
	if (fp->base == NULL)
		return 0;
	if (used == 0) 
		return 0;
	else
		write(fp->fd, fp->base, used);
	fp->ptr = fp->base;
	fp->cnt = bufsize; 
	return 0;
}

/* _fclose:  close file stream and flush output buffer or discard input buffer */
int fclose(FILE *fp)
{
	int stat = 0;

	if (fp->flag & _WRITE)
		stat = fflush(fp);
	free(fp->base);
	close(fp->fd);
	fp->base = fp->ptr = NULL;
	fp->cnt = fp->flag = 0;	
	fp->fd = -1;
	return (stat == EOF) ?  EOF : stat;
}

