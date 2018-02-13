#include <msp430.h> 

#define	RED	0x0001
#define RED_OFF	0x00FE
#define ENABLE_RED	0xFFFE
#define	DEVELOPMENT	0x5A80

/*
 * main.c
 */
int main(void) {
    WDTCTL = DEVELOPMENT;	// Stop watchdog timer
	PM5CTL0 = ENABLE_RED;
	P1DIR = RED;
	long x = 0;
	
	while(1)
	{
		for(x=0; x < 20000; x++);
		P1OUT = RED;
		for(x=0; x < 20000; x++);
		P1OUT = RED_OFF;
	}

}
