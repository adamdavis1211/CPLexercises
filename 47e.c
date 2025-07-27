#include <stdio.h>
#include <stdlib.h>	/* for atof() */
#include <math.h>
#include <ctype.h>

#define MAXOP 	100	/* max size of operand or operator */
#define NUMBER 	'0' 	/* signal that a number was found */
#define TOP '#'
#define POW '^'
#define CLEAR '!'
#define SWAPTOP '~'
#define SINE '@'
#define EXP '`'
#define VAR 'v'

#define VARIABLES 26
double variables[VARIABLES];
/* Write a routine ungets(s) that will push back an entire string onto the
input. Should ungest know about buf and bufp, or should it just use ungetch? */

int getop(char []);
void push(double);
double pop(void);
void peek(void);
void clear(void);
void swaptop(void);
void duptop(void);

/* reverse Polish calculator */
main() {
	int type;
	double op2;
	char s[MAXOP];
	
	while ((type = getop(s)) != EOF) {
		switch (type) {
			case NUMBER:
				push(atof(s));
				break;
			case '+':
				push(pop() + pop());
				break;
			case '%':
				op2 = pop();
				if (op2 != 0)
					push((int) pop() % (int) op2);
				else 
					printf("error: zero divisor\n");
				break;
			case '*':
				push(pop() * pop());
				break;
			case '-':
				op2 = pop();
				push(pop() - op2);
				break;
			case '/':
				op2 = pop();
				if (op2 != 0.0) 
					push(pop() / op2);
				else 
					printf("error: zero divisor\n");
				break;
			case CLEAR:
				clear();
				break;
			case SWAPTOP:
				swaptop();
				break;
			case SINE:
				push(sin(pop()));
				break;
			case EXP:
				push(exp(pop()));
				break;
			case POW:
				op2 = pop();
				push(pow(pop(), op2));
				break;
			case TOP:
				peek();
				break;
			case VAR: 
				printf("variable declaration: %s\n", s);
				variables[s[0]-'a'] = atof(s+1);
				break;
			case '\n':
				printf("result: %.8g\n", pop());
				break;
			default:
				if (isalpha(type))
					push(variables[type-'a']);
				else 
					printf("error: unknown command %s\n", s);
				break;
		}
	}
	return 0;
}				


#define MAXVAL 100	/* maximum depth of val stack */

int sp = 0;		/* next free stack position */
double val[MAXVAL];	/* value stack */

/* push: push f onto value stack */
void push(double f) {
	if (sp < MAXVAL)
		val[sp++] = f;
	else 
		printf("error: stack full, can't push %g\n", f);
}

/* pop: pop and return top value from stack */
double pop(void) {
	if (sp > 0) 
		return val[--sp];
	else {
		printf("error: stack empty\n");
		return 0.0;
	}
}

void peek(void) {
	if (sp > 0)
		printf("top of stack: %g\n", val[sp-1]);
	else 
		printf("error: stack empty\n");
}

void clear(void) {
	if (sp > 0) {
		sp = 0;
		printf("stack cleared.\n");
	}
	else 
		printf("stack is already empty\n");	
}

void swaptop(void) {
	double tmp;

	if (sp > 1) {
		tmp = val[sp-1];
		val[sp-1] = val[sp-2];
		val[sp-2] = tmp;			
	}
	else 
		printf("1 or 0 elements on the stack\n");
}
		
void duptop(void) {
	if (sp > 0 && sp < MAXVAL) { 
		val[sp] = val[sp-1];
		sp++;
	}
	else 
		printf("stack is empty or stack is full\n");
}

#include <ctype.h>


int getch(void);
void ungetch(int);
void ungets(char s[]);

/* getop: get next character or numeric operand */
int getop(char s[]) {
	int i, c, d;

	d = -1; 
	while ((s[0] = c = getch()) == ' ' || c == '\t');
	if (!isdigit(c) && c != '.' && c != '-') {
		if (isalpha(c) && (isdigit(d = getch()) || d == '-')) {
			s[i=1] = d;
			while (isdigit(d = getch())) 
				s[++i] = d ;
			ungetch(d);
			s[++i] = '\0';
			return VAR;	/* variable now bound to number */
		}
		else {
			if (d != -1) {
				ungetch(d);
				d = -1;
			}
			return c;	/* not a number */
		}
	}
	s[1] = '\0';
	if (c == '-' && !isdigit(d = getch())) {
		ungetch(d);
		return c;
	}	
	else if (c == '-' && isdigit(d)) { 
		s[i=0] = c, s[++i] = d;
		while (isdigit(s[++i] = d = getch()));
		s[i] = '\0';
		return NUMBER;
	}
	i = 0;
	if (isdigit(c))		/* collect integer part */
		while (isdigit(s[++i] = c = getch()))
			;
	if (c == '.')		/* collect fraction part */
		while (isdigit(s[++i] = c = getch()))
			;
	s[i] = '\0';
	if (c != EOF)
		ungetch(c);
	return NUMBER;
}


#define BUFSIZE 100

char buf[BUFSIZE];	/* buffer for ungetch */
int bufp = 0;		/* next free position in buf */

int getch(void) {	/* get a (possibly pushed-back) character */
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) { 	/* push character back on input */
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else 
		buf[bufp++] = c;
}			

void ungets(char s[]) {
	int i;	
	
	i = 0;
	for (i = 0; s[i] != '\0'; i++);
	for (i -= 1; i >= 0; i--)
		ungetch(s[i]);
}
