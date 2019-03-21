#include <stdio.h>

char *s = "Hello world!\n";

int main()
{
	*(s+6) = 'W';
	printf("%s", s);

	return 0;
}
