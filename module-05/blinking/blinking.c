#include <wiringPi.h>

int main (void)
{
	wiringPiSetup();
	pinMode(0, OUTPUT);
	
	for (;;)
	{
		digitalWrite(0, HIGH);
		delay(50);
		digitalWrite(0, LOW);
		delay(50);
	}

	return 0;
}
