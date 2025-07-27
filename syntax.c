#include <stdio.h>

#define MAX 20
#define TEXT 0
#define BRCK 1

int main() {
	int c, stateind;
	int symcount[MAX]; 	/* keep track of how many out standing matches are needed */
	for (c = 0; c < MAX; ++c) {symcount[c] = 0;}
	int ss[MAX]; 		/* state stack for determining new state after symbol match */

	stateind = 0;
	while ((c = getchar()) != EOF) {
		if (c == '{') { 
			ss[++stateind] = BRCK;		/* add new state on top of state stack */ 
			++symcount[BRCK]; 
		}
		else if (c == '}' && ss[stateind] == BRCK) {
			--symcount[BRCK];
			--stateind;
		}		
	}
	printf("%d unclosed brackets in code\n", symcount[BRCK]);
}
		
