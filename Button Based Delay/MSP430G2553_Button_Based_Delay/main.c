#include <msp430.h> 


/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	P1SEL = 0;      //Set up P1 as GPIO
	P1DIR |= BIT0;  //SET P1.0 AS OUTPUT

	P1DIR &= ~BIT3;  //SET P1.3 AS INPUT
    P1REN |= BIT3;              //Set pullup resistor for P1.3
	P1IE |= BIT3;   //ENABLE INTERRUPT ON BIT3
	P1IES |= BIT3;  //P1.3 AS FALLING EDGE TRIGGER
	P1IFG &= ~BIT3; //CLEAR INTERRUPT FLAG

	TACTL = TASSEL_1 + MC_1;
	TACCTL0 |= CCIE;                          // Compare-mode interrupt.
	TACCR0 = 50000;
	_BIS_SR(GIE);               //Enables Global Interrupt

	while(1){

	}
}

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    if((P1IES & BIT3) == BIT3)
    {
        P1IES &= ~BIT3;
        TACTL = TACLR;
        TACTL = TASSEL_1 + MC_2 + ID_3;
    }
    else
    {
        TACTL = TASSEL_1 + MC_0 + ID_3;
        P1IES |= BIT3;                      //Set as falling edge
        TACCR0 = TA0R;
        TACTL = MC_1 + TASSEL_1 + ID_3;
    }
    P1IFG &= ~BIT3;
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A(void)
{
    P1OUT ^= BIT0;
}
