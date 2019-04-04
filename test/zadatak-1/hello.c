#include "helloLib.h"

int main()
{
	int a = 22;
	int b = 55;
	int c;

	printFirstNumber(a);
	printSecondNumber(b);
	c = addNumbers(a, b);
	printResult(c);

	return 0;
}
