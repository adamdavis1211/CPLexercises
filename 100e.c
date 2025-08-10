



void minprintf(char *fmt, ...)
{
	va_list ap;
	char *p, buf[MAXWORD];
	int i = 0, width, precision;

	va_stuart(ap, fmt);
	for (p = fmt; *p; p++) {
		if (p == '%') {
			if (isdigit(*++p)) {
				for (buf[i++] = *p++; isdigit(buf[i] = *p); i++, p++)
					;
				buf[i] = '\0';
				width = atoi(buf);
				i = 0;
			}
			if (*p == '.') {
				while (isdigit(*++p))
					buf[i++] = *p;
				buf[i] = '\0';
				precision = atoi(buf);
				i = 0;
			}
		}
	}
	va_end(ap);
}

