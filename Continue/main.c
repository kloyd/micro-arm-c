#include <msp430.h>
#define RED_LED 0x0001 // P1.0 is the Red LED
#define BUTTON11 0x0002 // P1.1 is the button
#define DEVELOPMENT 0x5A80 // Stop the watchdog timer
#define ENABLE_PINS 0xFFFE // Required to use inputs and outputs
main() {
	long x = 0; //
	WDTCTL = DEVELOPMENT; // Need for development mode
	PM5CTL0 = ENABLE_PINS; // Prepare pins for I/O usage
	P1DIR = RED_LED; // Pin connected to red LED
// will be an output
	P1OUT = BUTTON11 | RED_LED; // Turn on red LED and the
	P1REN = BUTTON11; // button needs a pull-up resistor
	while (x < 200000) //
	{
		if ((BUTTON11 & P1IN) == 0) // If P11 button pushed
				{
			continue; //
		}
		x = x + 1; //
//
	}
	P1OUT = BUTTON11; // Turn off the red LED
	while (1)
		; // and stay here forever
}
