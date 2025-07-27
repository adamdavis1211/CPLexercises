



/* rewrite this loop without || or && logical operators */


for (i = 0; i < lim-1 && (c = getchar()) != '\n' && c != EOF; ++i)
	s[i] = c;



i = 0; 
while (i < lim-1) {
	c = getchar();
	if ( c == '\n' )
		i = lim-1;
	else if ( c == EOF ) 
		i = lim-1;
	else {
		s[i] = c;
		++i;
	}
}
