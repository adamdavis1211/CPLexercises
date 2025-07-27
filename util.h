#ifndef UTIL_H
#define UTIL_H

int get_line(char s[], int lim);
int bitcount(unsigned x);
int binsearch(int x, int v[], int n);
int escape(char s[], char t[], int maxlen);
void unescape(char s[], char t[], int maxlen);
void shellsort(int v[], int n);
void expand(char s1[], char s2[]);
double my_atof(char s[]);
void writelines(char *lineptr[], int nlines);
int readlines(char *lineptr[], int nlines);
void swap(void *[], int, int);

#endif
