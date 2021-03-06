#include <msp430.h>
#define RED_LED 0x0001 			// P1.0 is the Red LED

#define RED_OFF 0x00FE 	// Used to turn off the Red LED

#define BUTTON11 0x0002 		// P1.1 is the button

#define DEVELOPMENT 0x5A80 		// Stop the watchdog timer

#define ENABLE_PINS 0xFFFE 		// Required to use inputs and outputs

#define GREEN_ON 0x80
#define GREEN_OFF 0x7F
#define BUTTON12 0x04  // P1.2 lower right button (S2)


main()
{
	WDTCTL = DEVELOPMENT; 		// Need for development mode
	PM5CTL0 = ENABLE_PINS; 		// Prepare pins for I/O usage
	P1DIR = RED_LED; 			// Pin connected to red LED
								// will be an output

	P9DIR = GREEN_ON;

	P1OUT = BUTTON11 | BUTTON12; 			// Button needs a pull-up resistor
	P1REN = BUTTON11 | BUTTON12;
	while(1) 					// Keep looping forever
	{
		while((BUTTON11 & P1IN) == 0) 	// Is P11 button pushed?
		{
			P1OUT = P1OUT | RED_LED; 	// Turn on the Red LED
		}
		P1OUT = P1OUT & RED_OFF; 	// Turn off the Red LED

		while((BUTTON12 & P1IN) == 0)
		{
			P9OUT = P9OUT | GREEN_ON;
		}

		P9OUT = P9OUT & GREEN_OFF;
	}
}
