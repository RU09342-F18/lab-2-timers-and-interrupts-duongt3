#include <msp430.h> 


/**
 * main.c
 */
void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	    // stop watchdog timer

	P1SEL = 0;                      //Set P1 as GPIO
	P1DIR |= (BIT0 | BIT6);         //Set up P1.0 and P1.6 as output

	TA0CTL = TASSEL_1 + MC_1 + TAIE + ID_2;     //Set up Timer CTL as ACLK in UP mode
	TA0CCTL1 |= CCIE;                           //Set up TimerA0 in the compare mode

	TA0CCR0 = 30000;
	TA0CCR1 = 10000;

    _BIS_SR(GIE);               //Enables Global Interrupt

    while(1){

    }
}

#pragma vector=TIMER0_A1_VECTOR
__interrupt void Timer_A(void)
{
    switch(TA0IV)
    {
     case 2:
        P1OUT ^= BIT0;              //Flips the LED when interrupt is triggered
        CCR1 += 10000;              //Offsets CR1
        break;
     case 4:
         break;
     case 10:
         P1OUT ^= BIT6;
         CCR1 = 10000;              //Sets CR1 back to its original value
         break;
    }
}

