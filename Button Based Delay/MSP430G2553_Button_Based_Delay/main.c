#include <msp430.h> 


/**
 * File: main.c
 * Author: Timothy Duong
 * Date Created: 9/27/18
 *
 * Used on MSP430G2553 to blink an LED depnding on how long the user holds the button
 */

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	P1SEL = 0;          //Set up P1 as GPIO
	P1DIR |= BIT0;      //Set P1.0 as an output

	P1DIR &= ~BIT3;      //Set P1.3 as an input
    P1REN |= BIT3;       //Set pullup resistor for P1.3
	P1IE |= BIT3;        //Enable interrupt for P1.3
	P1IES |= BIT3;       //Set interrupt to trigger as falling edge
	P1IFG &= ~BIT3;      //Clear interrupt flag

	TACTL = TASSEL_1 + MC_1;    //Set TimerA in ACLK and in UPmode
	TACCTL0 |= CCIE;            // Enable Compare-mode interrupt
	TACCR0 = 50000;             //Set CCR0 to 50000.
	_BIS_SR(GIE);               //Enables Global Interrupt

	while(1){

	}
}

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    //If the button is pressed, an interrupt occurs. Reset the counter and keep track of how long the button is pressed.
    //Change interrupt flag to rising edge and clear interrupt flag.
    //When button is released, trigger interrupt to set current CCR0 to current timer count. Change timer settings to original value.

    if((P1IES & BIT3) == BIT3)  //If the interrupt occurs at P1.3
    {
        P1IES &= ~BIT3;         //Set interrupt on rising edge
        TACTL = TACLR;          //Clear the CTL
        TACTL = TASSEL_1 + MC_2 + ID_3; //Set TimerA CTL in ACLK, UPmode, internal divider of 8
    }
    else
    {
        TACTL = TASSEL_1 + MC_0 + ID_3;     //Stop timer
        P1IES |= BIT3;                      //Set as falling edge
        TACCR0 = TA0R;                      //Store current count in CCR0
        TACTL = MC_1 + TASSEL_1 + ID_3;     //Restore timer setting: Aclk, UPmode, internal divier 8
    }
    P1IFG &= ~BIT3;         //Clear interrupt
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A(void)
{
    P1OUT ^= BIT0;      //Flip LED
}
