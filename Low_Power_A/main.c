#include <msp430.h> 

#define STOP_WATCHDOG   0x5A80
#define ACLK            0x0100
#define UP              0x0010
#define ENABLE_PINS     0xFFFE

main()
{
    WDTCTL = STOP_WATCHDOG;

    PM5CTL0 = ENABLE_PINS;
    P1DIR = BIT0;

    TA0CCR0 = 20000;     // 25us * 20000 - 0.5s
    TA0CTL = ACLK + UP;
    TA0CCTL0 = CCIE;

    _BIS_SR(LPM0_bits | GIE);

    while(1);
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer0_ISR(void)
{
    P1OUT = P1OUT ^ BIT0; // toggle led
}
