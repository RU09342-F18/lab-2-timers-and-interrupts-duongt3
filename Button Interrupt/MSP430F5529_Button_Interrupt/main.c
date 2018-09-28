#include <msp430.h> 


/**
 * File: main.c
 * Author: Timothy Duong
 * Date Created: 9/27/18
 *
 * Used on MSP430F5529 to blink LED P1.0 whenever P2.1 is pressed.
 */

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    P1DIR |= BIT0;              //Set P1.0 as output
    P1OUT &= ~BIT0;             //Set the initial output for P1.0 as 0

    P2DIR &= ~BIT1;             //Set P2.1 as input
    P2REN |= BIT1;              //Set pullup resistor for P1.3
    P2OUT |= BIT1;              //Set initial value for P2.1 output as 1

    P2IE |= BIT1;               //Set Interrupt enable for P1.1
    P2IES |= BIT1;              //Set Interrupt for the rising edge
    P2IFG &= ~BIT1;             //Clear Interrupt Flag
    _bis_SR_register(GIE);      //Enables Global Interrupt

}
#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void)
{
    P1OUT ^= BIT0;             //Flips the LED when interrupt is triggered
    P2IFG &= ~BIT1;            //Clears the interrupt flag
    __delay_cycles(5000);
}

