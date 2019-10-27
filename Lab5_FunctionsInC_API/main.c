// ***** 0. Documentation Section *****
// main.c
//     Runs on TM4C123
//     UART runs at 115,200 baud rate
//     Daniel Valvano
//     June 17, 2013
// Lab 5
//      Jon Valvano and Ramesh Yerraballi
//      January 15, 2016

/*
 * Add the include directory: C:\ti\TivaWare_C_Series-2.1.4.178
 * And the library file: driverlib.lib that is found at: C:\ti\TivaWare_C_Series-2.1.4.178\driverlib\ccs\Debug
 *
 */
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
uint32_t CalcArea(uint32_t l, uint32_t w);
void ConfigureUART(void);
uint32_t ConvertNumber(char *s, uint32_t *l);

// ***** 3. Subroutines Section *****
int main(void)
{
    uint32_t length = 10, width = 5, area;
    char string_buffer[4];

    // Initialize first the PLL and then the UART PA0-1
    SysCtlClockSet(
    SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ); // set system clock to 80 MHz and use the 16 MHz crystal
    volatile uint32_t clock = SysCtlClockGet(); // get system clock
    // Initialize UART
    ConfigureUART();

    UARTprintf("\nThis program calculates areas of rectangular rooms.\n");
    while (1)
    {
        UARTprintf("\nWhat is the width of the room?: ");
        UARTgets(string_buffer, 4);
        // UARTprintf("%s\n", string_buffer);
        if (!ConvertNumber(string_buffer, &width))
        {
            UARTprintf("\nInvalid entry");
            width = 0;
        }
        UARTprintf("\nWhat is the length of the room?: ");
        UARTgets(string_buffer, 4);
        // UARTprintf("%s\n", string_buffer);
        if (!ConvertNumber(string_buffer, &length))
        {
            UARTprintf("\nInvalid entry");
            length = 0;
        }

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
uint32_t CalcArea(uint32_t l, uint32_t w)
{
// Put your Lab 5 code here
    if (l < 3 | l > 20 | w < 3 | w > 20)
    {
        return (0);
    }

    return (l * w);
}

// Configures the UART on PA0 and PA1 to
// use the COM port for transferring data to the PC
// Input: n.a.
// Output: n.a.
// Notes:
// Sets the COM to:
// 115200 bps, use 8 bit, no parity, and 1 stop bit
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
    // UART_CLOCK_PIOSC or UART_CLOCK_SYSTEM
    UARTClockSourceSet(UART0_BASE, UART_CLOCK_SYSTEM);
    volatile int clock = UARTClockSourceGet(UART0_BASE);

    //
    // Initialize the UART for console I/O.
    // 16000000 or 80000000
    UARTStdioConfig(0, 115200, 80000000);
}

// Converts a string that represents a whole number
// to a corresponding unsigned integer
// Input: a string s that represents the number ending with \0
// Output: the corresponding whole number as an unsigned integer
// Note: the function returns a 1 if the conversion succeeds
//       otherwise a 0 is returned
uint32_t ConvertNumber(char *s, uint32_t *l)
{
    uint32_t result = 0;
    while (*s != '\0')
    {
        result *= 10;
        // test if in range
        if (*s < '0' & *s > '9')
            return 0;
        else
        {
            result += (*s - '0');
        }

        s += 1; // next one
    }

    *l = result;
    return 1;
}
