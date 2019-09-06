/**
 * main.c
 */
// This is your first program to run on the LaunchPad
// You will run this program without modification as your Lab 2
// If the left switch SW1 is
//      not pressed the LED toggles blue-red
//      pressed the LED toggles blue-green
// 0.Documentation Section
// main.c
// Runs on LM4F120 or TM4C123
// Lab2_HelloLaunchPad, Input from PF4, output to PF3,PF2,PF1 (LED)
// Authors: Daniel Valvano, Jonathan Valvano and Ramesh Yerraballi
// Date: January 15, 2016
// LaunchPad built-in hardware
// SW1 left switch is negative logic PF4 on the Launchpad
// SW2 right switch is negative logic PF0 on the Launchpad
// red LED connected to PF1 on the Launchpad
// blue LED connected to PF2 on the Launchpad
// green LED connected to PF3 on the Launchpad
// includes
#include <stdint.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"
#include "gpio.h"
#include "sysctl.h"
#include "hw_memmap.h"

//  Defines

//   Global Variables

//   Function Prototypes
void PortF_Init(void);
void Delay(void);

// 3. Subroutines Section
// MAIN: Mandatory for a C Program to be executable
int main(void)
{
    PortF_Init();        // Call initialization of port PF0-4
    while (1)
    {
        if (!GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4))
        {              // zero means SW1 is pressed
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3 | GPIO_PIN_2 |GPIO_PIN_1, GPIO_PIN_3);
        }
        else
        {                      // 0x10 means SW1 is not pressed
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3 | GPIO_PIN_2 |GPIO_PIN_1, GPIO_PIN_1);
        }
        Delay();                     // wait 0.1 sec
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3 | GPIO_PIN_2 |GPIO_PIN_1, GPIO_PIN_2);
        Delay();                     // wait 0.1 sec
    }
}

// Subroutine to initialize port F pins for input and output
// PF4 and PF0 are input SW1 and SW2 respectively
// PF3,PF2,PF1 are outputs to the LED
// Inputs: None
// Outputs: None
// Notes: These five pins are connected to hardware on the LaunchPad
void PortF_Init(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);  // 1) F enable
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))
    {                                            // 2) wait for port F to be ready
    }
    GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;  // 2) unlock PortF PF0
    GPIO_PORTF_CR_R = 0x1F;           // allow changes to PF4-0
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4 | GPIO_PIN_0); // PF0, PF4 input
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_3 | GPIO_PIN_2 | GPIO_PIN_1); // PF3, PF2, PF1 output
    // enable pullup resistors on PF4,PF0
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4 | GPIO_PIN_0, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
}
// Color    LED(s) PortF
// dark     ---    0
// red      R--    0x02
// blue     --B    0x04
// green    -G-    0x08
// yellow   RG-    0x0A
// sky blue -GB    0x0C
// white    RGB    0x0E
// pink     R-B    0x06

// Subroutine to wait 0.1 sec
// Inputs: None
// Outputs: None
// Notes: ...
void Delay(void)
{
    unsigned long volatile time;
    time = 727240 * 200 / 91;  // 0.1sec
    while (time)
    {
        time--;
    }
}

