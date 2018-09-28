#include <msp430.h> 


/**
 * File: main.c
 * Author: Timothy Duong
 * Date Created: 9/27/18
 *
 * Used on MSP430FR2311 to blink LED at P1.0 for how long the user holds down the button at P1.1.
 */

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    P1SEL0 = 0;         //Set up P1 as GPIO
    P1DIR |= BIT0;      //Set P1.0 as output

    P1DIR &= ~BIT1;     //Set P1.3 as input
    P1REN |= BIT1;      //Set pullup resistor for P1.3
    P1IE |= BIT1;       //Enable interrupt on P1.1
    P1IES |= BIT1;      //P1.1 set interrupt to trigger on falling edge
    P1IFG &= ~BIT1;     //Clear interrupt flag

    TBCTL = TBSSEL_1 + MC_1;    //Set TimerB control to ACLK in UPMODE
    TBCCTL0 |= CCIE;            //Enable capture compare interrupt
    TBCCR0 = 25000;             //Set value in CCR0 to 25000
    _BIS_SR(GIE);               //Enables Global Interrupt

    PM5CTL0 &= ~LOCKLPM5;       // Disable the GPIO power-on default high-impedance mode
                                // to activate previously configured port settings
    while(1){

    }
}

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    //If the button is pressed, an interrupt occurs. Reset the counter and keep track of how long the button is pressed.
    //Change interrupt flag to rising edge and clear interrupt flag.
    //When button is released, trigger interrupt to set current CCR0 to current timer count. Change timer settings to original value.

    if((P1IES & BIT1) == BIT1)  //If the interrupt occurs at P1.1
    {
        P1IES &= ~BIT1;         //Set the interrupt to trigger on the rising edge
        TBCTL = TBCLR;          //Clear the current CTL
        TBCTL = TBSSEL_1 + MC_2 + ID_3; //Select ACLK, continuous mode, internal divider 8
    }
    else
    {
        TBCTL = TBSSEL_1 + MC_0 + ID_3; //Stops the current timer
        P1IES |= BIT1;                  //Set interrupt as falling edge
        TBCCR0 = TB0R;                  //Store the current count into CCR0
        TBCTL = MC_1 + TBSSEL_1 + ID_3; //Restore clock to resume counting
    }
    P1IFG &= ~BIT1;                     //Clear interrupt flag
}

#pragma vector=TIMER0_B0_VECTOR
__interrupt void Timer_B(void)
{
    P1OUT ^= BIT0;  //Blinks the LED at P1.0 everytime counter counts to CCR0
}

