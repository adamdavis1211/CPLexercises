#include <stdio.h>
#include "util.h"

int main() {
	char s[] = "76.14321e2";
	printf("%f\n", my_atof(s));
}
