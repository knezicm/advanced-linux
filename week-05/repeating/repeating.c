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
		delay(80);
		digitalWrite(0, HIGH);
		delay(320);
		digitalWrite(0, LOW);
		delay(110);
		digitalWrite(0, HIGH);
		delay(45);
		digitalWrite(0, LOW);
		delay(70);
		digitalWrite(0, HIGH);
		delay(120);
		digitalWrite(0, LOW);
		delay(30000);
	}

	return 0;
}
