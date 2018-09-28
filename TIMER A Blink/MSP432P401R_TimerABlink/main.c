#include "msp.h"



/**
 * File: main.c
 * Author: Timothy Duong
 * Date Created: 09/27/18
 *
 * Used on the MSP432P401 to toggle 2 LEDs using timer and CCR.
 */

void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

	P1DIR |= BIT0;         //Set up P1.0 and P1.6 as output
	P2DIR |= BIT0;         //Set up P1.0 and P1.6 as output

	TIMER_A0->CTL = TIMER_A_CTL_TASSEL_1 |    // ACLK
	            TIMER_A_CTL_MC_1 |            // Continuous mode
	            TIMER_A_CTL_CLR |             // Clear TAR
	            TIMER_A_CTL_IE;               // Enable timer overflow interrupt

	TIMER_A0->CCTL[1] = TIMER_A_CCTLN_CCIE;   //Enable CCIE for CCR1
	TA0CCR0 = 30000;
    TA0CCR1 = 10000;

	__enable_irq();//Enables Global Interrupt

    NVIC->ISER[0] = 1 << ((TA0_N_IRQn) & 31);   //What does this do? Still need this line of code

}

void TA0_N_IRQHandler(void)
{
    switch(TA0IV)       //TA0 Interrupt vector values
    {
    case 2:
        P1->OUT ^= BIT0;              //Flips the LED when interrupt is triggered
        TA0CCR1 += 10000;             //Offsets CR1
        break;
        //Bunch of do nothings
    case 4:
    case 6:
    case 8:
    case 10:
    case 12:
        break;
    case 14:
        P2->OUT ^= BIT0;              //Toggle P2.0
        TA0CCR1 = 10000;              //Sets CR1 back to its original value
        break;
    }
    // Clear timer overflow interrupt flag
    TIMER_A0->CTL &= ~TIMER_A_CTL_IFG;
}


