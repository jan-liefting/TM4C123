/*
 * PLL.c
 *
 *  Created on: 14 sep. 2019
 *      Author: Jan
 */


// bus frequency is 400MHz/(SYSDIV2+1) = 400MHz/(4+1) = 80 MHz
// see the table at the end of this file

#include <stdint.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"
#include "PLL.h"
// The #define statement SYSDIV2 initializes
// the PLL to the desired frequency.
// #define SYSDIV2 4
// bus frequency is 400MHz/(SYSDIV2+1) = 400MHz/(4+1) = 80 MHz

// configure the system to get its clock from the PLL
void PLL_Init(void)
{
    // 0) configure the system to use RCC2 for advanced features
    //    such as 400 MHz PLL and non-integer System Clock Divisor
    SYSCTL_RCC2_R |= SYSCTL_RCC2_USERCC2;
    // 1) bypass PLL while initializing
    SYSCTL_RCC2_R |= SYSCTL_RCC2_BYPASS2;
    // 2) select the crystal value and oscillator source
    SYSCTL_RCC_R &= ~SYSCTL_RCC_XTAL_M;// clear XTAL field
    SYSCTL_RCC_R += SYSCTL_RCC_XTAL_16MHZ;// configure for 16 MHz crystal
    SYSCTL_RCC2_R &= ~SYSCTL_RCC2_OSCSRC2_M;// clear oscillator source field
    SYSCTL_RCC2_R += SYSCTL_RCC2_OSCSRC2_MO;// configure for main oscillator source
    // 3) activate PLL by clearing PWRDN
    SYSCTL_RCC2_R &= ~SYSCTL_RCC2_PWRDN2;
    // 4) set the desired system divider and the system divider least significant bit
    SYSCTL_RCC2_R |= SYSCTL_RCC2_DIV400;// use 400 MHz PLL
    // clear system clock divider field
    SYSCTL_RCC2_R = (SYSCTL_RCC2_R&~0x1FC00000) + (SYSDIV2<<22);// configure for 80 MHz clock
    // 5) wait for the PLL to lock by polling PLLLRIS
    while((SYSCTL_RIS_R&SYSCTL_RIS_PLLLRIS)==0)
    {};
    // 6) enable use of PLL by clearing BYPASS
    SYSCTL_RCC2_R &= ~SYSCTL_RCC2_BYPASS2;
}

