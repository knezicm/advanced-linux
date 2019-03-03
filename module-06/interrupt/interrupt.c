#include <wiringPi.h>
#include <stdio.h>

#define BUTTON	0
#define LED	2	

static volatile unsigned int delay_ms;

// Interrupt handler
static void interruptHandler()
{
	delay_ms += 1000;
	
	if (delay_ms > 5000)
		delay_ms = 1000;
	
	printf("Delay is %d\n", delay_ms);
}

int main(void)
{
	wiringPiSetup();

	// Initialize the delay to 1 sec
	delay_ms = 1000;
	
	// Set up LED pin to output mode and initialize it to LOW
	pinMode(LED, OUTPUT);
	digitalWrite(LED, LOW);

	// Set up BUTTON pin to input mode and enable its pull-up resistor
	pinMode(BUTTON, INPUT);
	pullUpDnControl(BUTTON, PUD_UP);
	
	// Register interrupt handler
	wiringPiISR(BUTTON, INT_EDGE_FALLING, &interruptHandler);

	for (;;)
	{
		digitalWrite(LED, HIGH);
		delay(delay_ms/2);
		digitalWrite(LED, LOW);
		delay(delay_ms/2);
	}
	
	return 0;
}
