/* There is no error checking in day_of_year or month_day. Remedy
 * this defect. */

static char daytab[2][13] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

/* day_of_year:  set day of year from month & day */
int day_of_year(int year, int month, int day) 
{
	int i, leap;

		
	leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
	if (year < 0 || month < 1 || month > 12 || day > daytab[leap][i] || day < 1)
		return -1;
	for (i = 1; i < month; i++)
		day += daytab[leap][i];
	return day;
}

/* month_day:  set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday)
{
	int i, leap, daycount;

	leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
	daycount = (leap == 1) 366 : 365;
	if (year < 0 || yearday < 1 || yearday > daycount)
		return -1;

	for (i = 1; yearday > daytab[leap][i]; i++)
		yearday -= daytab[leap][i];
	*pmonth = i;
	*pday = yearday;
}

