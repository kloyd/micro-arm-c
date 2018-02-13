#include <msp430.h>
#define RED_LED 0x0001 // P1.0 is the Red LED
#define ENABLE_PINS 0xFFFE // Required to use inputs and outputs
#define ACLK 0x0100 // Timer_A ACLK source
#define UP 0x0010 // Timer_A UP mode
// #define TAIFG 0x0001 // Used to look at Timer A Interrupt FlaG
#define PET_WATCHDOG 0x5A08 // WDT password and pet
#define GREEN_LED 0x80


main() {
	unsigned char intervals = 0; // Will be used to count ~1 second
	PM5CTL0 = ENABLE_PINS; // Enable inputs and outputs
	TA0CCR0 = 400; // We will count up from 0 to 400 (~10ms)
	TA0CTL = ACLK | UP; // Use ACLK, for UP mode
	P1DIR = RED_LED;
	P9DIR = GREEN_LED;
	while (1) {
		if (TA0CTL & TAIFG) // If timer has counted ~10ms
		{
			WDTCTL = PET_WATCHDOG; // Pet watchdog
			TA0CTL = TA0CTL & (~TAIFG); // Count another 10ms
			P9OUT = P9OUT ^ GREEN_LED;
			intervals = intervals + 1; // Increment 10ms steps
			if (intervals == 100) // Has 100*10ms = 1s elapsed?
			{
				P1OUT = P1OUT ^ RED_LED; // Then toggle red LED
				intervals = 0; // Begin 1s count again
			}
		}
	} //end while(1)
} //end main()
