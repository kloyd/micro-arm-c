#include <msp430.h> 

#define STOP_WATCHDOG   0x5A80
#define ACLK            0x0100
#define UP              0x0010
#define ENABLE_PINS     0xFFFE
#define SLOW            0x00C0 // slow down ACLK by factor of 8.

main()
{
    WDTCTL = STOP_WATCHDOG;

    PM5CTL0 = ENABLE_PINS;
    P1DIR = BIT0;
    P1OUT = 0x00;        // make sure led is off

    TA0CCR0 = 40000;     // 40000 * 200us = 8s
    TA0CTL = ACLK | UP | SLOW;
    TA0CCTL0 = CCIE;

    _BIS_SR(LPM0_bits | GIE);

    while(1);
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer0_ISR(void)
{
    if(TA0CCR0 == 40000)
        {
            TA0CCR0 = 125;
            P1OUT = BIT0;
        }
    else
        {
            TA0CCR0 = 40000;
            P1OUT = 0x00;
        }
}
