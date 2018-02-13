// Program to look at counting in hexadecimal
#include <msp430.h> // Used to make code easier to read

#define DEVELOPMENT 0x5A80 // Used to disable watchdog timer for development

main() {
	WDTCTL = DEVELOPMENT; // Disable watchdog timer for development
	long count = 0; // Create variable named count and set equal to 0
	
	while (count < 0xFFFF) // Keep going until count is really big
	{
		count = count + 1; // Add 1 to variable count
	}
	while (1);   // After counting, stay here forever
}
