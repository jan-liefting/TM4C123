// This is your second program to run on the LaunchPad
// You will debug this program as your Lab 4
// If both switches SW1 and SW2 are pressed, the LED should be blue
// If just SW1 switch is pressed,            the LED should be red
// If just SW2 switch is pressed,            the LED should be green
// If neither SW1 or SW2 is pressed,         the LED should be off

// 0.Documentation Section
// main.c
// Runs on LM4F120 or TM4C123
// Lab4_IO, Inputs from PF4,PF0, output to PF3,PF2,PF1 (LED)
// Authors: Daniel Valvano, Jonathan Valvano and Ramesh Yerraballi
// Date: January 15, 2016

// LaunchPad built-in hardware
// SW1 left switch is negative logic PF4 on the Launchpad
// SW2 right switch is negative logic PF0 on the Launchpad
// red LED connected to PF1 on the Launchpad
// blue LED connected to PF2 on the Launchpad
// green LED connected to PF3 on the Launchpad

// 0. Pre-processor Directives Section

// 1. Includes
#include <stdint.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"
#include "gpio.h"
#include "sysctl.h"
#include "hw_memmap.h"

// 2. Declarations Section
//   Global Variables
int32_t SW;  // input from PF4,PF0

//   Function Prototypes
void PortF_Init(void);
void Delay(void);

// 3. Subroutines Section
// MAIN: Mandatory for a C Program to be executable
int main(void)
{
    PortF_Init();     // Call initialization of port PF4, PF3, PF2, PF1, PF0
    while (1)
    {
        SW = GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4) ^ (GPIO_PIN_0 | GPIO_PIN_4);
        // read SW1 and SW2; toggle bits to reflect negative logic

        switch (SW)
        {
        case (0x00):
                    GPIO_PORTF_DATA_R = 0x00;
        break; // neither are pressed; LED is off
        case (0x01):
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3 | GPIO_PIN_2 |GPIO_PIN_1, GPIO_PIN_3);
        break; // SW2 pressed; LED is green
        case (0x10):
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3 | GPIO_PIN_2 |GPIO_PIN_1, GPIO_PIN_1);
        break; // SW1 pressed; LED is red
        case (0x11):
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3 | GPIO_PIN_2 |GPIO_PIN_1, GPIO_PIN_2);
        break; // both pressed; LED is blue
        }
    }
}
// Subroutine to initialize port F pins for input and output
// PF4 and PF0 are input SW1 and SW2 respectively
// PF3,PF2,PF1 are outputs to the LED
// Inputs: None
// Outputs: None
// Notes: These five pins are connected to hardware on the LaunchPad
//void PortF_Init(void)
//{
//    volatile unsigned long delay;
//    SYSCTL_RCGC2_R |= 0x00000020;     // 1) F clock
//    delay = SYSCTL_RCGC2_R;           // delay
//    GPIO_PORTF_LOCK_R = 0x4C4F434B;   // 2) unlock PortF PF0
//    GPIO_PORTF_CR_R = 0x1F;           // allow changes to PF4-0
//    GPIO_PORTF_AMSEL_R = 0x00;        // 3) disable analog function
//    GPIO_PORTF_PCTL_R = 0x00000000;   // 4) GPIO clear bit PCTL
//    GPIO_PORTF_DIR_R = 0x0E;          // 5) PF4,PF0 input, PF3,PF2,PF1 output
//    GPIO_PORTF_AFSEL_R = 0x00;        // 6) no alternate function
//    GPIO_PORTF_PUR_R = 0x11;        // enable pullup resistors on PF4,PF0
//    GPIO_PORTF_DEN_R = 0x1F;          // 7) enable digital pins PF4-PF0
//}

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

