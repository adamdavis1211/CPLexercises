#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#define MAXNUMS 100
#define MAX 20
/* Rewrite the postfix calculator of Chapter 4 to use scanf and/or sscanf
to do the input and number conversion */

static double nums[MAXNUMS];
void push(double);
double pop(void);
int sp = 0;

int main()
{
	int i, rv;
	unsigned char digits[MAX], operator, blank;
	double operand;

	while (1) {
		if (scanf("%10[0-9.+-]", digits) == 1) {
			if (isdigit(digits[0]) || isdigit(digits[1])) {
				push(atof(digits));
				continue;
			}
			else 
				ungetc(digits[0], stdin);
		}
		if (scanf("%1[+*/-]", &operator) == 1) {
			switch (operator) {
			case '+':
				push(pop() + pop());
				break;
			case '-': 
				operand = pop();
				push(pop() - operand);
				break;
			case '*':
				push(pop() * pop());
				break;
			case '/':
				operand = pop();
				push(pop() / operand);
				break;
			}
		}
		else if (scanf("%1[ \n\t]", &blank) == 1) 
			if (blank == '\n')
				printf("%.2f\n", pop());
	}
}

double pop(void) {
	if (sp > 0)
		return nums[--sp];
	else
		printf("error: stack empty\n");
}

void push(double operand)
{
	if (sp < MAXNUMS)
		nums[sp++] = operand;
	else
		printf("error: stack full, can't push %g\n", operand);
}
