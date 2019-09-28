// ***** 0. Documentation Section *****
// main.c
//     Runs on TM4C123
//     UART runs at 115,200 baud rate
//     Daniel Valvano
//     June 17, 2013
// Lab 5
//      Jon Valvano and Ramesh Yerraballi
//      January 15, 2016

// ***** 1. Pre-processor Directives Section *****
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"

// ***** 2. Global Declarations Section *****

// FUNCTION PROTOTYPES: Each subroutine defined
unsigned long CalcArea(unsigned long l, unsigned long w);
void ConfigureUART(void);

// ***** 3. Subroutines Section *****
int main(void)
{
    unsigned long length = 10, width = 5, area;

    // Initialize first the PLL and then the UART PA0-1
    SysCtlClockSet(
            SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN
                    | SYSCTL_XTAL_16MHZ); // set system clock to 80 MHz
    volatile uint32_t clock = SysCtlClockGet(); // get system clock
    // Initialize UART
    ConfigureUART();

    UARTprintf("\nThis program calculates areas of rectangular rooms.\n");
    while (1)
    {
        UARTprintf("\nGive length: ");
        //UARTscanf("%i", &length);  // Get input
        UARTprintf("\nGive width: ");
        //UARTscanf("%i", &width);   // Get input
        area = CalcArea(length, width);
        UARTprintf("\nArea of the room = %i\n", area);
    }
}

// Computes the Area of a rectangular room whose sides are given
// Input:  the length (l) and width (w) are the dimensions of a rectangle
// Output: the area of the rectangular room
// Notes:  Return a result of zero if
//    the length is less than 3,
//    the width is less than 3,
//    the length is greater than 20 or
//    the width is greater than 20.
unsigned long CalcArea(unsigned long l, unsigned long w)
{
//  unsigned long result;

// Put your Lab 5 code here
    if (l < 3 | l > 20 | w < 3 | w > 20)
    {
        return (0);
    }

    return (l * w);
}

void ConfigureUART(void)
{
    //
    // Enable the GPIO Peripheral used by the UART.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    //
    // Enable UART0
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    //
    // Configure GPIO Pins for UART mode.
    //
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    //
    // Use the system clock as the UART clock source.
    //
    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);
    volatile int clock = UARTClockSourceGet(UART0_BASE);

    //
    // Initialize the UART for console I/O.
    //
    UARTStdioConfig(0, 115200, 16000000);
}
