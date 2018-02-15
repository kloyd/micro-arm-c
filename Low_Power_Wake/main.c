#include <msp430.h> 

#define STOP_WATCHDOG   0x5A80  // Stop the watchdog timer
#define ACLK            0x0100  // Timer ACLK source
#define UP              0x0010  // Timer UP mode
#define ENABLE_PINS     0xFFFE  // Required to use inputs and outputs
#define SLOW            0x00C0  // Slows down ACLK by factor of 8

main()
{
    WDTCTL = STOP_WATCHDOG;

    PM5CTL0 = ENABLE_PINS;

    P1DIR = BIT0;
    P1OUT = 0x00;

    P9DIR = BIT7;
    P9OUT = 0x00;

    TA0CCR0 = 50000;
    TA0CTL = ACLK | UP | SLOW;
    TA0CCTL0 = CCIE;

    //P1OUT = 0x01;   // red led on (wastes electricity... but would be okay if it was controlling a l

    _BIS_SR(LPM0_bits | GIE);

    P1OUT = 0x00; // red off when wake up.
    P9OUT = BIT7;  // green on when wake up.

    while(1);
}

// Timer0 Interrupt Service Routine
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer0_ISR(void)
{
    _BIC_SR(LPM0_EXIT);
}
