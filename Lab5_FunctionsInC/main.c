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
#include <stdio.h>   // standard C library
#include "PLL.h"
#include "UART.h"    // functions to implement input/output

// ***** 2. Global Declarations Section *****

/*
 * Opmerking: er is een issue met de stdio functies printf en scanf
 * Deze werken niet goed; daarom worden er geen getallen afgedrukt of ingelezen
 *
 */

// FUNCTION PROTOTYPES: Each subroutine defined
unsigned int Calc_Area(unsigned int l, unsigned int w);

// ***** 3. Subroutines Section *****
int main(void)
{
    unsigned int length, width, area;

    // Initialize first the PLL and then the UART PA0-1
    PLL_Init();     // initialize the clock for 80 MHz
    UART_Init();    // initialize UART for printing

    printf("\nThis program calculates areas of rectangular rooms.\n");
    while (1)
    {
        printf("\nGive length: ");
        scanf("%u", &length);  // Get input
        printf("\nGive width: ");
        scanf("%u", &width);   // Get input
        area = Calc_Area(length, width);
        printf("\nArea of the room = %u\n", area);
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
unsigned int Calc_Area(unsigned int l, unsigned int w)
{
//  unsigned long result;

// Put your Lab 5 code here
    if (l < 3 | l > 20 | w < 3 | w > 20)
    {
        return (0);
    }

    return (l * w);
}
