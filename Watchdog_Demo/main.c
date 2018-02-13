#include <msp430.h>

#define ENABLE_RED 0xFFFE // Used to enable microcontroller's pins
#define RED_LED 0x0001 // P1.0 is the red LED
#define STOP_WATCHDOG 0x5A80 // Stop the watchdog

main() {
	// WDTCTL = STOP_WATCHDOG; // Notice, we have commented this out
	PM5CTL0 = ENABLE_RED; // Use pins as inputs and outputs
	P1DIR = RED_LED; // Set the red LED as an output
	P1OUT = RED_LED; // Turn on the red LED
	while (1) // Infinitely loop until watchdog timer
	{ // counter overflows and microcontroller
	} // program will restart
}
