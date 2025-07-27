#include <stdio.h>
#define MAX 20

#define S_TEXT	0 	/* state: in plain text */
#define S_COMM	1	/* state: in comment */ 	
#define S_SL  	2	/* state: in string literal */
#define S_CC	3 	/* state: in character constant */ 
#define S_ESCS	4	/* state: in escape sequence */ 
#define S_PCOM 	5	/* state: pre-comment symbol read */
#define S_ECOM 6	/* state: post-comment symbol read */
#define S_ESCC 7

#define BRK 0		/* bracket */
#define PAR 1		/* paratheses */
#define BRC 2		/* braces */	
#define QUO 3		/* quote */
#define SQO 4		/* single quote */
#define COMM 5
#define SYMS 6

int main() {
	int c, state;
	int symcount[SYMS]; 	/* keep track of how many out standing matches are needed */
	for (c = 0; c < SYMS; ++c) {symcount[c] = 0;}

	state = S_TEXT;
	while ((c = getchar()) != EOF) {

		if (c == '{' && state == S_TEXT) ++symcount[BRK]; 
		else if (c == '}' && state == S_TEXT) --symcount[BRK]; 
		else if (c == '(' && state == S_TEXT) ++symcount[PAR]; 
		else if (c == ')' && state == S_TEXT) --symcount[PAR]; 
		else if (c == '[' && state == S_TEXT) ++symcount[BRC]; 
		else if (c == ']' && state == S_TEXT) --symcount[BRC]; 
		else if (c == '/' && state == S_TEXT) state = S_PCOM;
		else if (c!= '*' && state == S_PCOM) state = S_TEXT; 
		else if (c == '*' && state == S_PCOM) { state = S_COMM; ++symcount[COMM];}
		else if (c == '*' && state == S_COMM) state = S_ECOM; 
		else if (c != '/' && state == S_ECOM) state = S_COMM; 
		else if (c == '/' && state == S_COMM) { state = S_TEXT; --symcount[COMM];}
		else if (c == '"' && state == S_TEXT) { state = S_SL; ++symcount[QUO]; }
		else if (c == '\\' && state == S_SL) state = S_ESCS;
		else if (state == S_ESCS) state = S_SL;
		else if (c == '"' && state == S_SL) { state = S_TEXT; --symcount[QUO]; }
		else if (c == '\'' && state == S_TEXT) { state = S_CC; ++symcount[SQO]; }
		else if (c == '\\' && state == S_CC) state = S_ESCC;
		else if (state == S_ESCC) state = S_CC;
		else if (c == '\'' && state == S_CC) { state = S_TEXT; --symcount[SQO]; }
	}
	if (symcount[BRK] > 0) printf("%d missing closing brackets in code\n", symcount[BRK]);
	else if (symcount[BRK] < 0) printf("%d missing opening brackets in code\n", -symcount[BRK]);
	if (symcount[PAR] > 0) printf("%d missing closing parantheses in code\n", symcount[PAR]);
	else if (symcount[PAR] < 0) printf("%d missing opening parentheses in code\n", -symcount[PAR]);
	if (symcount[BRC] > 0) printf("%d missing closing braces in code\n", symcount[BRC]);
	else if (symcount[BRC] < 0) printf("%d missing opening braces in code\n", -symcount[BRC]);
	if (symcount[QUO] > 0) printf("%d unclosed string literals", symcount[QUO]);
	if (symcount[SQO] > 0) printf("%d unclosed char constant", symcount[SQO]);
	if (symcount[COMM] > 0) printf("%d unclosed comment", symcount[COMM]);
}
		
