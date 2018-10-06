# TIMER A Blink
TimerA blink utilizes the TIMERA module built in to the microprocessor to blink 2 LEDs at different rates. The timer module utilizes two capture compare registers CCR0 and CCR1. When the counter counts up to the value stored in CCR1, a timer interrupt will trigger. In this case, the interrupt will cause one LED to switch states and add an offset to CCR1. Then, the counter will eventually count to CCR0, which will trigger the second LED to switch states. At the same time, CCR1 is set back to its original value.

No Futher implementation is needed after uploading the code.
