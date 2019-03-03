#include <wiringPi.h>
#include <stdio.h>

#define BUTTON	0
#define LED	2	

static unsigned int delay_ms;

// Function for scanning the state of BUTTON pin and making some action
static void scanButton()
{
	if (digitalRead(BUTTON) == HIGH)
		return;

	delay_ms += 1000;
	
	if (delay_ms > 5000)
		delay_ms = 1000;
	
	printf("Delay is %d\n", delay_ms);

	while (digitalRead(BUTTON) == LOW);
		delay(10);
}

int main(void)
{
	wiringPiSetup();
	// Set the initial delay to 1 sec
	delay_ms = 1000;

	// Set LED pin to output mode and initialize it to LOW
	pinMode(LED, OUTPUT);
	digitalWrite(LED, LOW);

	// Set BUTTON pin to input mode and enable its pull-up resistor
	pinMode(BUTTON, INPUT);
	pullUpDnControl(BUTTON, PUD_UP);

	for (;;)
	{
		// Poll the current state of the button and update the delay
		scanButton();
		
		// Make some actions
		digitalWrite(LED, HIGH);
		delay(delay_ms/2);
		digitalWrite(LED, LOW);
		delay(delay_ms/2);
	}
	
	return 0;
}
