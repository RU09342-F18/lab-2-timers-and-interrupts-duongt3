#include <msp430.h> 


/**
 * main.c
 */
void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    P1SEL0 = 0;      //Set up P1 as GPIO
    P1DIR |= BIT0;  //SET P1.0 AS OUTPUT

    P1DIR &= ~BIT1;  //SET P1.3 AS INPUT
    P1REN |= BIT1;              //Set pullup resistor for P1.3
    P1IE |= BIT1;   //ENABLE INTERRUPT ON BIT3
    P1IES |= BIT1;  //P1.3 AS FALLING EDGE TRIGGER
    P1IFG &= ~BIT1; //CLEAR INTERRUPT FLAG

    TBCTL = TBSSEL_1 + MC_1;
    TBCCTL0 |= CCIE;                          // Compare-mode interrupt.
    TBCCR0 = 25000;
    _BIS_SR(GIE);               //Enables Global Interrupt

    PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode
                                            // to activate previously configured port settings
    while(1){

    }
}

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    if((P1IES & BIT1) == BIT1)
    {
        P1IES &= ~BIT1;
        TBCTL = TBCLR;
        TBCTL = TBSSEL_1 + MC_2 + ID_3;
    }
    else
    {
        TBCTL = TBSSEL_1 + MC_0 + ID_3;
        P1IES |= BIT1;                      //Set as falling edge
        TBCCR0 = TB0R;
        TBCTL = MC_1 + TBSSEL_1 + ID_3;
    }
    P1IFG &= ~BIT1;
}

#pragma vector=TIMER0_B0_VECTOR
__interrupt void Timer_B(void)
{
    P1OUT ^= BIT0;
}

