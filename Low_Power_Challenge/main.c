#include <msp430.h> 

#define STOP_WATCHDOG   0x5A80  // Stop the watchdog timer
#define ACLK            0x0100  // Timer ACLK source
#define UP              0x0010  // Timer UP mode
#define ENABLE_PINS     0xFFFE  // Required to use inputs and outputs

#define RED_LED 0x0001          // P1.0 is the Red LED
#define RED_OFF 0x00FE  // Used to turn off the Red LED

#define BUTTON11 0x0002

/*
 * main.c
 */
int main(void) {
    // 1) Stop the watchdog
    WDTCTL = STOP_WATCHDOG;

    PM5CTL0 = ENABLE_PINS;

    // 2) Enable P1.0 to be an output with the red LED initially off
    P1DIR = RED_LED;

    // 3) Enable P1.1 to be an input for the push-button switch.
    P1OUT = BUTTON11;
    // (Do not forget to enable the pull-up resistor!)
    P1REN = BUTTON11;

    // 4) Set up the timer to generate an interrupt every 50ms (0.05s).
    // This will require a TA0CCR0 value of 2000 (do not use the #define SLOW).
    // 50ms / 25us = 2000
    TA0CCR0 = 2000;
    TA0CTL = ACLK | UP;
    TA0CCTL0 = CCIE;

    // 5) Put the microcontroller into Low Power Mode 0.
    _BIS_SR(LPM0_bits | GIE);

    // 10) Keep repeating steps 6-9.// Stop watchdog timer
    while(1);

}

// Timer0 Interrupt Service Routine
// 6) Every 50ms, the program will jump to the Timer0 interrupt service routine.
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer0_ISR(void)
{
    // 7) Each time you are in the ISR, check to see if the P1.1 push-button is pushed.
    if((BUTTON11 & P1IN) == 0) {
            // 9) If the button is ever pushed, turn on the red LED and end the ISR to go back to main()
            //to return to low power mode.
            P1OUT = P1OUT | RED_LED;
    } else {
            // 8) If the button is not pushed, make sure the red LED is off,
            // and end the ISR to go back to main() to return to low power mode.
            P1OUT = P1OUT & RED_OFF;
    }
}


