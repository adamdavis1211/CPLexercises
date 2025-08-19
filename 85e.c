/* Modify the fsize program to print the other information contained in the 
inode entry */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>		/* flags for read and write */
#include <sys/types.h>		/* typedefs */
#include <sys/stat.h>		/* structure returned by stat */
#include <time.h>
#include "dirent.h"

void fsize(char *);

/* print file name */
int main(int argc, char **argv)
{
	if (argc == 1)		/* default: current directory */
		fsize(".");
	else
		while (--argc > 0)
			fsize(*++argv);
	return 0;
}

void dirwalk(char *, void (*fcn)(char *));

/* fsize:  print the name of file "name" */
void fsize(char *name)
{
	struct stat stbuf;

	if (stat(name, &stbuf) == -1) {
		fprintf(stderr, "fsize: can't access %s\n", name);
		return;
	}
	if ((stbuf.st_mode & S_IFMT) == S_IFDIR)
		dirwalk(name, fsize);
	struct tm *tm_info = localtime(&stbuf.st_atim.tv_sec);
	char buf[100];
	strftime(buf, sizeof buf, "%Y-%m-%d %H:%M:%S", tm_info);
	printf("size: %-8ld name: %-18s uid: %-8u LAT: %s\n", 
		stbuf.st_size, name, stbuf.st_uid, buf);
}

#define MAX_PATH 1024

/* dirwalk:  apply fcn to all files in dir */
void dirwalk(char *dir, void (*fcn)(char *))
{
	char name[MAX_PATH];
	struct dirent *dp;
	DIR *dfd;

	if ((dfd = opendir(dir)) == NULL) {
		fprintf(stderr, "dirwalk: can't open %s\n", dir);
		return;
	}
	while ((dp = readdir(dfd)) != NULL) {
		if (strcmp((dp->d_name), ".") == 0 || strcmp(dp->d_name, "..") == 0)
			continue;
		if (strlen(dir)+strlen(dp->d_name)+2 > sizeof(name))
			fprintf(stderr, "dirwalk: name %s %s too long\n", dir, dp->d_name);
		else {
			sprintf(name, "%s/%s", dir, dp->d_name);
			(*fcn)(name);
		}
	}
	closedir(dfd);
}



