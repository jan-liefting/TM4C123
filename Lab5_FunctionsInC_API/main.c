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
 * Add the include directory: ~\ti\TivaWare_C_Series-2.1.4.178
 * And the library file: driverlib.lib that is found at: ~\ti\TivaWare_C_Series-2.1.4.178\driverlib\ccs\Debug
 *
 */
// ***** 1. Pre-processor Directives Section *****
#include <stdint.h> // translates specific int-types to the corresponding C types
#include <stdbool.h> // defines true and false

#include "driverlib/sysctl.h" // Prototypes for the system control driver.

//local include files
#include "uartstdio.h"
#include "configureuart0.h"

// ***** 2. Global Declarations Section *****

// FUNCTION PROTOTYPES: Each subroutine defined
uint32_t CalcArea(uint32_t l, uint32_t w);
uint32_t ConvertNumber(char *s, uint32_t *l);

// ***** 3. Subroutines Section *****
int main(void)
{
    uint32_t length = 10, width = 5, area;
    char string_buffer[4];

    // Initialize first the PLL and then the UART PA0-1
    // set system clock to 80 MHz and use the 16 MHz crystal
    SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
    volatile uint32_t clock = SysCtlClockGet(); // get system clock
    // Initialize UART
    ConfigureUART0();
    //Initialize UARTSTDIO package
    UARTStdioConfig(0, 115200, 80000000);

    UARTprintf("\nThis program calculates areas of rectangular rooms\n");
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

//************************************************************************
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

//***************************************************************
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
