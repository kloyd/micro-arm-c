#include <msp430.h> // Allows us to use "short-cut" names
#define ENABLE_RED 0xFFFE // Used to enable microcontroller's pins
#define DEVELOPMENT 0x5A80 // Used to disable some of the security
// features while we are still learning
main() // All C programs have a main function
{
	WDTCTL = DEVELOPMENT; // Disables some security features
	PM5CTL0 = ENABLE_RED; // Enables the pins to the outside world
	P9DIR = BIT6; // P9.6 will be connected to yellow LED
	long x = 0; // Will be used to slow down blinking
	while (1) // Continuously repeat everything below
	{
		for (x = 0; x < 30000; x = x + 1)
			; // Count from 0 to 30,000 for a delay
		P9OUT = BIT6; // Turn on new yellow LED
		for (x = 0; x < 30000; x = x + 1)
			; // Count from 0 to 30,000 for a delay
		P9OUT = 0x00; // Turn off new yellow LED
	}
}
