#include <stdio.h>
/* Define a macro swap(ta, x, y) that interchanges two arguments of
type t. (Block structure will help.) */

#define	 paste(front, back)  front ## back
#define  swap(t, x, y)  do {t tmp = x; x = y; y = tmp;} while (0)

main() {
	double i = 331213.213123;
	double j = 65454.12321;
	swap(double, i, j);
	printf("i: %g, j: %g\n", i, j);
}
