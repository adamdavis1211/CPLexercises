/* Write the program expr, which evaluates a reverse Polish expression from the
command line, where each operator or operand is a separate argument. 

ex: expr 2 3 4 + *; evaluates to 2*(3+4) */

/* pseudo

	1. add numbers as they appear onto the stack.
	2. as operand appears, perform operation on top two numbers,
	   pop them, and stack the result .

*/
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

void num_push(int);
int num_pop();

int main(int argc, char *argv[])
{
	int top, i, w;
		
	while (--argc > 0) {
		if (isdigit( w = (*++argv)[0]) || w == '-') {	
			if (w == '-' && !isdigit((*argv)[1])) {
				printf("invalid argument: \"%s\"\n", *argv);
				return -1;
			} else {	
				for (i = 1; (w = (*argv)[i]) != '\0'; i++) 
					if (!isdigit(w)) {
						printf("invalid argument: \"%s\"\n", *argv);
						return -1;
					}
			}
			num_push(atoi(*argv));
		}
		else 
			switch ((*argv)[0]) {
			case '*':
				num_push(num_pop() * num_pop());
				break;
			case '+':
				num_push(num_pop() + num_pop());
				break;
			case '/': 
				top = num_pop();
				num_push(num_pop() / top);
				break;
			case '-': 
				top = num_pop();
				num_push(num_pop() - top);
				break;
			default:
				printf("invalid argument: \"%s\"\n", *argv);
				return -1;
		}
	}
	printf("%d\n", num_pop());
	return 0;
}



#define MAXNUMS 100
int num_stack[MAXNUMS];
int sp;		/* points to next free position */

void num_push(int num) 
{
	if (sp > MAXNUMS-1)
		printf("num_push: stack is full, cannot push: %d\n", num);
	else
		num_stack[sp++] = num;
}

int num_pop()
{
	if (sp < 1) {
		printf("num_pop: stack is empty\n");	
		return 0;
	}
	else
		return num_stack[--sp];
}
