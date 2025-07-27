#include "dcl.h"
#include <string.h>
#include <stdio.h>

extern int tokentype;
extern char token[];
extern char out[];
extern char name[];
extern int err_state;
extern char parambuf[];

int gettoken(void);

/* dcl:  parse a declarator */
void dcl(void)
{
	int ns;

	for (ns = 0; gettoken() == '*';)	/* count *'s */
		ns++;
	dirdcl();
	while (ns-- > 0)
		strcat(out, " pointer to");
}

/* dirdcl:  parse a direct declarator */
void dirdcl(void)
{
	int type;
	
	if (tokentype == '(' ) {	/* ( dcl ) */
		dcl();
		if (tokentype != ')') {
			printf("error: missing )\n");
			err_state = ERROR;
		}
	} else if (tokentype == NAME)	/* variable name */
		strcpy(name, token);
	else {
		printf("error: expected name or (dcl)\n");
		err_state = ERROR;
	}
	while ((type=gettoken()) == PARENS || type == BRACKETS)
		if (type == PARENS) {
			strcat(out, " function");
			strcat(out, parambuf);
			strcat(out, " returning");
		}
		else {
			strcat(out, " array");
			strcat(out, token);
			strcat(out, " of");
		}
}
