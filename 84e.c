/* The standard library function 
	int fseek(FILE *fp, long offset, int origin)
is identical to lseek except that fp is a file pointer instead of a file descriptor
and return value is an int status, not a position. Write fseek. Make sure that your 
fseek coordinates properly with the buffering done for the other functions of the
library. */

int fseek(FILE *fp, long offset, int origin)
{
	long rc;

	if (fp->flag & _WRITE) 
		if (fflush(fp) == EOF)
			return EOF;
	if (fp->flag & _READ) {
		if (origin == SEEK_CUR)
			offset -= fp->cnt;
		fp->ptr = fp->base;
		fp->cnt = 0;
	}
	rc = lseek(fp->fd, offset, origin);
	return (rc == -1) ? EOF : 0;
}
