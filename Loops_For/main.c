#include <msp430.h> 

#define RED_ON	0x0001
#define RED_OFF	0x0000
#define DEVELOPMENT	0x5A80
#define ENABLE_IO	0xFFFE

/*
 * main.c
 */
int main(void) {
    WDTCTL = DEVELOPMENT;
    PM5CTL0 = ENABLE_IO;
    P1DIR = RED_ON;
    P1OUT = RED_ON;

    long x;

    for(x=0; x<30000; x=x+1)
    {

    }

    P1OUT = RED_OFF;

    while(1);
}
