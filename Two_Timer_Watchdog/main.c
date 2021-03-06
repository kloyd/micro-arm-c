#include <msp430.h>

#define RED_LED         0x0001    // P1.0 is the Red LED
#define GREEN_LED       0x0080    // P9.7 is Green LED
#define GREEN_OFF       0x007F
#define BUTTON11        0x0002
#define STOP_WATCHDOG   0x5A80    // Stop the watchdog timer
#define ACLK            0x0100    // Timer ACLK source
#define UP              0x0010    // Timer Up mode
#define ENABLE_PINS     0xFFFE    // Required to use inputs and outputs
#define PET_WATCHDOG    0x5A08

void setup_input_outputs(void);
void setup_led_outputs(void);
void setup_p1_button(void);
void setup_timer0(void);
void setup_timer1(void);
void enable_timers(void);

main ()
{

  setup_input_outputs ();
  setup_led_outputs();
  setup_p1_button ();

  setup_timer0();

  setup_timer1();

  enable_timers();

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
__interrupt void Timer0_ISR (void)  // This officially names this ISR as "Timer0_ISR"
//************************************************************************
{
  P1OUT = P1OUT ^ RED_LED;  // Toggle red LED
}

// ISR for Timer 1
#pragma vector=TIMER1_A0_VECTOR
__interrupt void Timer1_ISR(void)
{
  WDTCTL = PET_WATCHDOG; // Pet watchdog
}

void setup_input_outputs(void)
{
  PM5CTL0 = ENABLE_PINS;
}

void setup_led_outputs(void)
{
  P1DIR = RED_LED;              // Set Red LED as an output
  P9DIR = GREEN_LED;
}

void setup_p1_button(void)
{
  P1OUT = BUTTON11;
  P1REN = BUTTON11;
}

void setup_timer0(void)
{
  TA0CCR0 = 40000;              // Sets value of Timer_0
  TA0CTL = ACLK | UP;           // Set ACLK, UP MODE
  TA0CCTL0 = CCIE;              // Enable interrupt for Timer_0
}

void setup_timer1(void)
{
  TA1CCR0 = 400;  // 10 ms pet watchdog
  TA1CTL = ACLK | UP;
  TA1CCTL0 = CCIE;
}

void enable_timers (void)
{
  _BIS_SR(GIE);                 // Activate interrupts previously enabled
}
