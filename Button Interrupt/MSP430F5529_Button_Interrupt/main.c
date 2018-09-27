#include <msp430.h> 


/**
 * main.c
 */
void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    P1DIR |= BIT0;              //Set P1.0 as output
    P1OUT &= ~BIT0;             //Set the output for P1.0

    P2DIR &= ~BIT1;
    P2REN |= BIT1;              //Set pullup resistor for P1.3
    P2OUT |= BIT1;

    P2IE |= BIT1;               //Set Interrupt enable for P1.1
    P2IES |= BIT1;              //Set Interrupt for the rising edge
    P2IFG &= ~BIT1;             //Clear Interrupt Flag
    _bis_SR_register(GIE);               //Enables Global Interrupt

}
#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void)
{
    P1OUT ^= BIT0;               //Flips the LED when interrupt is triggered
    P2IFG &= ~BIT1;            //Clears the interrupt flag
    __delay_cycles(5000);
}

