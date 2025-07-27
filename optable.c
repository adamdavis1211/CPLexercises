#include <stdio.h>

char *optable[16];

int main() 
{
	int i;

	optable[0 ] = "Operators				Associativity\n";
	optable[1 ] = "() [] . -> 				left to right\n";
	optable[2 ] = "++ -- + - ! ~ * & (type) sizeof		right to left\n";
	optable[3 ] = "* / %					left to right\n";
	optable[4 ] = "+ -					left to right\n"; 
	optable[5 ] = "<< >> 					left to right\n";
	optable[6 ] = "< <= > >=				left to right\n";	
	optable[7 ] = "== !=					left to right\n";	
	optable[8 ] = "&					left to right\n";	
	optable[9 ] = "^					left to right\n";	
	optable[10] = "|					left to right\n";	
	optable[11] = "&&					left to right\n";	
	optable[12] = "||					left to right\n";	
	optable[13] = "?:					right to left\n";	
	optable[14] = "= += -= *= /= %= &= |= ^= <<= >>= 	right to left\n";	
	optable[15] = ",					left to right\n";	
	for (i = 0; i < 16; i++)
		printf("%s", optable[i]);
}
	
