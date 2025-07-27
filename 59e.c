/* Rewrite the routines of day_of_year and month_day with pointers instead of
 * indexing */

#include <stdio.h>
#define COLS 13
#define ROWS 2
#define days(A, B, C)  *(*((A)+(B))+(C)) 

static char daytab[ROWS][COLS] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

/* day_of_year:  set day of year from month & day */
int day_of_year(int year, int month, int day) 
{
	int i, leap;

		
	leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
	if (year < 0 || month < 1 || month > 12 || day < 1 || day > days(daytab, leap, month))
		return -1;
	for (i = 1; i < month; i++)
		day += days(daytab, leap, i);
	return day;
}

/* month_day:  set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday)
{
	int i, leap, daycount;

	leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
	daycount = (leap == 1) ? 366 : 365;
	if (year < 0 || yearday < 1 || yearday > daycount)
		return;

	for (i = 1; yearday > days(daytab, leap, i); i++)
		yearday -= days(daytab, leap, i);
	*pmonth = i;
	*pday = yearday;
}

void main() {
	int year, month, day;

	year = 2025;
	month = 7;
	day = 20;
	printf("%d\n", day_of_year(year, month, day));

}
