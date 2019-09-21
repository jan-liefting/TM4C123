// BranchingFunctionsDelays.c Lab 6
// Runs on LM4F120/TM4C123
// Use simple programming structures in C to
// toggle an LED while a button is pressed and
// turn the LED on when the button is released.
// This lab will use the hardware already built into the LaunchPad.
// Daniel Valvano, Jonathan Valvano
// January 15, 2016

// built-in connection: PF0 connected to negative logic momentary switch, SW2
// built-in connection: PF1 connected to red LED
// built-in connection: PF2 connected to blue LED
// built-in connection: PF3 connected to green LED
// built-in connection: PF4 connected to negative logic momentary switch, SW1

// 1. Includes
#include <stdint.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"
#include "gpio.h"
#include "sysctl.h"
#include "hw_memmap.h"

// function prototype
void Init_PF(void);
void Delay100ms(unsigned long);

int main(void)
{
    int32_t x;

    // initialization goes here
    // set clock PLL 80 MHz
    SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ); // set system clock to 80 MHz
    volatile uint32_t clock = SysCtlClockGet(); // get system clock

    Init_PF();

    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);

    while (1)
    {
        // body goes here
        if (!(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4)))
        {                       // if SW is pressed (negative logic)
            x = GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_2) ^ GPIO_PIN_2;  // Toggle pin 2
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, x);
            Delay100ms(4);      // delay toggle
        }
        else
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2); // turn blue LED on PF2
    }
}

// **************Delayms*********************
// Delays by time * 100ms
// Input: time
// Output: none
// Assumes:
void Delay100ms(unsigned long time)
{
    while (time > 0)
    {
        unsigned long i = 1333333;
        while (i > 0)
            i--;
        time--;
    }
}

// **************Init_PF*********************
// Initializes PF using SW1 on PF4 and the blue LED on PF2
// Input: none
// Output: none
// Assumes:
void Init_PF()
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);        // 1) F enable
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))
    {                                                   // 2) wait for port F to be ready
    }
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4);  // PF4 input
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_2); // PF2 output
    // enable pullup resistors on PF4
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
}

