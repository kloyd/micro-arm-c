#include <msp430.h>
#define ENABLE_PINS 0xFFFE // Enables inputs and outputs
void ADC_SETUP(void); // Used to setup ADC12 peripheral
main()
{
    WDTCTL = WDTPW | WDTHOLD; // Stop WDT
    PM5CTL0 = ENABLE_PINS; // Enable inputs and outputs
    P1DIR = BIT0; // Set RED LED to output

    ADC_SETUP(); // Sets up ADC peripheral

    ADC12IER0 = ADC12IE0; // Enable Interrupt for ADC

    _BIS_SR(GIE);           // Interrupts ON

    ADC12CTL0 = ADC12CTL0 | ADC12ENC; // Enable conversion
    ADC12CTL0 = ADC12CTL0 | ADC12SC; // Start conversion

    while(1);

} // end main()

//***********************************
//* ADC12 Interrupt Service Routine
//***********************************
#pragma vector = ADC12_VECTOR
__interrupt void ADC12_ISR(void)
{
    if (ADC12MEM0 > 0x800)
        {
            P1OUT = BIT0;
        }
    else
        {
            P1OUT = 0x00;
        }

    ADC12CTL0 = ADC12CTL0 | ADC12SC;
}
//************************************************************************
//* Configure Analog-to-Digital Converter peripheral**********************
//************************************************************************
void ADC_SETUP(void)
{
    #define ADC12_SHT_16 0x0200 // 16 clock cycles for sample and hold
    #define ADC12_ON 0x0010 // Used to turn ADC12 peripheral on
    #define ADC12_SHT_SRC_SEL 0x0200 // Selects source for sample & hold
    #define ADC12_12BIT 0x0020 // Selects 12-bits of resolution
    #define ADC12_P92 0x000A // Use input P9.2 for analog input
    ADC12CTL0 = ADC12_SHT_16 | ADC12_ON ; // Turn on, set sample & hold time
    ADC12CTL1 = ADC12_SHT_SRC_SEL; // Specify sample & hold clock source
    ADC12CTL2 = ADC12_12BIT; // 12-bit conversion results
    ADC12MCTL0 = ADC12_P92; // P9.2 is analog input
}
