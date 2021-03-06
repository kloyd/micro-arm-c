#include <msp430.h>
#define RED_LED 0x0001 // P1.0 is the red LED
#define RED_ON 0x0001
#define RED_OFF 0x007E

#define DEVELOPMENT 0x5A80 // Stop the watchdog timer
#define ENABLE_PINS 0xFFFE // Required to use inputs and outputs
#define ACLK 0x0100 // Timer_A ACLK source
#define UP 0x0010 // Timer_A UP mode
//#define TAIFG 0x0001 // Used to look at Timer A Interrupt FlaG
#define SECONDS 20

main()
{
	unsigned char intervals = 0; // Count number of 50,000 counts
	WDTCTL = DEVELOPMENT; // Stop the watchdog timer
	PM5CTL0 = ENABLE_PINS; // Enable inputs and outputs
	TA0CCR0 = 40000; // We will count up from 0 to 40,000 (40000 * 25us = 1 sec)
	TA0CTL = ACLK | UP; // Use ACLK, for UP mode
	P1DIR = RED_LED; // Set red LED as an output
    P1OUT = P1OUT | RED_ON;

	while (1) {
		if (TA0CTL & TAIFG) // If timer has counted to 40,000
		{
			intervals = intervals + 1; // Update number of 40,000 counts
			TA0CTL = TA0CTL & (~TAIFG); // Count again
			if (intervals == SECONDS) // If counted 10*40,000 = 400,000
					{
				intervals = 0; // Reset interval count
				P1OUT = P1OUT & RED_OFF; // Then, toggle red P1.0 LED
				break;
			}
		}
	}
	
	while(2)
	{

	}
}
