#include <msp430.h>
#define RED_ON 0x01 // Used to turn-on/enable P1.0 LED
#define RED_OFF 0xFE // Used to turn-off the P1.0 LED
#define BUTTON11 0x02 // P1.1 is S1
#define BUTTON12 0x04 // P1.2 is S2
#define DEVELOPMENT 0x5A80 // Stop the watchdog timer
#define ENABLE_IO 0xFFFE // Needed to enable I/O
#define GREEN_ON 0x80
#define GREEN_OFF 0x7F

main() {
	WDTCTL = DEVELOPMENT;			// Stop the watchdog for development
	PM5CTL0 = ENABLE_IO; 			// Required to use I/O
	P1DIR = RED_ON; 				// P1.0 will be an output
	P9DIR = GREEN_ON;  				// P9.2 green led out
	P1OUT = BUTTON11 | BUTTON12; 	// P1.1 will be an input
	P1REN = BUTTON11 | BUTTON12; 	// with a pull-up resistor

	while (1) // Keep doing this loop forever
	{
		if ( ( (BUTTON11 & P1IN) == 0 ) & ( (BUTTON12 & P1IN) == 0) ) // If P1.1 button pushed
		{
			P1OUT = P1OUT | RED_ON; // Turn on the Red LED
		}
		else // Else, if P1.1 is not pushed.
		{
			P1OUT = P1OUT & RED_OFF; // Turn off the red LED
		}

		if ((BUTTON12 & P1IN) == 0) // If P1.2 button pushed
		{
			P9OUT = P9OUT | GREEN_ON; // Turn on the Red LED
		}
		else // Else, if P1.2 is not pushed.
		{
			P9OUT = P9OUT & GREEN_OFF; // Turn off the red LED
		}
	}
}
