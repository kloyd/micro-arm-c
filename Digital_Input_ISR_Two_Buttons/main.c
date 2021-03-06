#include <msp430.h>

#define ENABLE_PINS 0xFFFE // Required to use inputs and outputs

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD; // Stop WDT

    PM5CTL0 = ENABLE_PINS; // Enable inputs and outputs

    P1DIR = BIT0; // P1.0 will be output for red LED
    P9DIR = BIT7; // P9.7 will be output for green LED

    P1OUT = BIT1 | BIT2; // Pull-up resistors for buttons
    P1REN = BIT1 | BIT2;

    P1IE = BIT1 | BIT2; // Enable interrupt for P1.1 and P1.2
    P1IES = BIT1 | BIT2; // For transitions from HI-->LO

    P1IFG = 0x00; // Ensure no interrupts are pending

    _BIS_SR(GIE); // Activate all interrupts

    while(1); // Infinite loop
}
//***********************************************************************
//* Port 1 Interrupt Service Routine
//***********************************************************************
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    unsigned long delay;  // Wait for bouncing to end
    for (delay = 0; delay < 12345; delay = delay + 1)
        ;

    switch (P1IV)
        // What is stored in P1IV?
        {

        case 4:  // Come here if P1.1 interrupt
            {
                P1OUT = P1OUT ^ BIT0;  // Toggle P1.0 for P1.1 push
                break;  // Then leave switch
            }

        case 6:  // Come here if P1.2 interrupt
            {
                P9OUT = P9OUT ^ BIT7;  // Toggle P9.7 for P1.1 push
                break;  // Then leave switch
            }

        }  // end switch statement

}  // end ISR
