# Button Interrupt
This lab utilizes interrupts so that the microprocessor isn't constantly polling the button. The code below is used in Code composer to trigger interrupts.

```c
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
}
```

When the button on the microprocessor is pressed, it will trigger the PORT1_VECTOR interrupt. The LED will change states and the interrupt vector will be cleared. 

