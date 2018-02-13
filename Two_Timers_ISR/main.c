#include <msp430.h>

#define RED_LED         0x0001    // P1.0 is the Red LED
#define GREEN_LED       0x0080    // P9.7 is Green LED
#define GREEN_OFF       0x007F
#define BUTTON11        0x0002
#define STOP_WATCHDOG   0x5A80    // Stop the watchdog timer
#define ACLK            0x0100    // Timer ACLK source
#define UP              0x0010    // Timer Up mode
#define ENABLE_PINS     0xFFFE    // Required to use inputs and outputs

main ()
{

  WDTCTL = STOP_WATCHDOG;       // Stop the watchdog timer
  PM5CTL0 = ENABLE_PINS;        // Required to use inputs and outputs

  P1DIR = RED_LED;              // Set Red LED as an output
  P9DIR = GREEN_LED;

  P1OUT = BUTTON11;                    // Button needs a pull-up resistor
  P1REN = BUTTON11;

  TA0CCR0 = 40000;              // Sets value of Timer_0
  TA0CTL = ACLK | UP;           // Set ACLK, UP MODE
  TA0CCTL0 = CCIE;              // Enable interrupt for Timer_0

  //TA1CCR0 = 10000;
  //TA1CTL = ACLK | UP;
  //TA1CCTL0 = CCIE;

  _BIS_SR(GIE);                 // Activate interrupts previously enabled

  while (1)
    {
      while ((BUTTON11 & P1IN) == 0)
        {
          P9OUT = P9OUT | GREEN_LED;
        }
      P9OUT = P9OUT & GREEN_OFF;
    }
}

//************************************************************************
// Timer0 Interrupt Service Routine
//************************************************************************
#pragma vector=TIMER0_A0_VECTOR
// The ISR must be put into a special
// place in the microcontroller program
// memory. That's what this line does.
// While you do not need this comment,
// the code line itself must always
// appear exactly like this in your
// program.
//************************************************************************
__interrupt void Timer0_ISR (void)  // This officially names this ISR as "Timer0_ISR"
//************************************************************************
{
  P1OUT = P1OUT ^ RED_LED;  // Toggle red LED
}
// When all the code is here done, the
// ISR ends and the program jumps back
// to wherever it was before
//************************************************************************

// ISR for Timer 1
#pragma vector=TIMER1_A0_VECTOR
__interrupt void Timer1_ISR(void)
{

}
