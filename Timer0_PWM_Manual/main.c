#include <msp430.h>
#define STOP_WATCHDOG 0x5A80 // Stop the watchdog timer
#define ACLK 0x0100 // Timer ACLK source
#define UP 0x0010 // Timer UP mode
#define ENABLE_PINS 0xFFFE // Required to use inputs and outputs

main() {
  WDTCTL = WDTPW | WDTHOLD;  // WDT Password + Hold (Stop)

  PM5CTL0 = ENABLE_PINS;  // Enable inputs and outputs

  P1DIR = BIT0;  // P1.0 red LED is output
  P1OUT = 0x00;  // and initially off

  TA0CTL = ACLK | UP;  // Count up to TA0CCR0 with 25us steps

  TA0CCR0 = 50000;  // Count 0-->50K then start at 0 again
  TA0CCTL0 = CCIE;  // CCR0 interrupt triggers when count equals TA0CCR0 (50K)

  TA0CCR1 = 45000;  // CCR1 interrupt triggers when count
  TA0CCTL1 = CCIE;  // equals TA0CCR1 (45K)

  _BIS_SR(GIE);  // Activate both enabled interrupts
  while (1)
    ;
}

#pragma vector=TIMER0_A1_VECTOR
__interrupt void Timer0_CCR1_MATCH(void) {
  if (TA0IV == 2)
    {
      P1OUT = BIT0;
    }
}

//************************************************************************
// Timer0 Interrupt Service Routine
//************************************************************************
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer0_CCR0_MATCH(void) {
  P1OUT = 0x00;
}

