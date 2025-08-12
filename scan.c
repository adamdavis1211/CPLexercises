#include <stdio.h>

void dog(void);
void kit(void);
void gin(void);

int main()
{
	gin();
}

void dog(void)	/* rudimentary calculator */
{
	double sum, v;
	
	sum = 0;
	while (scanf("%lf", &v) == 1)
		printf("\t%.2f\n", sum += v);
}

void kit(void)
{
	int day, month, year;

	scanf("%d/%d/%d", &day, &month, &year);
	printf("%d %d %d\n", day, month, year);
}

void gin(void)
{
	int day, month, year;
	char line[100], monthname[20];

	while (getline(line, &size, stdin) > 0) {
		if (sscanf(line, "%d %s %d" &day, monthname, &year) == 3)
			printf("valid: %s\n", line);
		else if (sscanf(line, "%d/%d/%d", &month, &day, &year) == 3)
			printf("valid: %s\n", line);
		else 
			printf("invalid: %s\n", line);
	}
