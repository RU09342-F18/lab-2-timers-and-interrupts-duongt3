#include <msp430.h> 


/**
 * File: main.c
 * Author: Timothy Duong
 * Date Created: 09/18/18
 *
 * Used on the MSP430G2553,
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	P1SEL = 0;                  //Set P1 as GPIO
	P1DIR |= BIT0;              //Set P1.0 as output
	P1DIR &= ~BIT3;             //Set P1.3 as input
	P1REN |= BIT3;              //Set pullup resistor for P1.3
	P1OUT &= ~BIT0;             //Set the output for P1.0

	P1IE |= BIT3;               //Set Interrupt enable for P1.3
	P1IES |= BIT3;              //Set Interrupt for the rising edge
	P1IFG &= ~BIT3;             //Clear Interrupt Flag
	_BIS_SR(GIE);               //Enables Global Interrupt

	while(1){

	}
}
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    P1OUT ^=0x01;               //Flips the LED when interrupt is triggered
    P1IFG &=~(BIT3);            //Clears the interrupt flag
}
