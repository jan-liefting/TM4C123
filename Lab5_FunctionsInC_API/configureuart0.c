/*
 * configureuart0.c
 *
 *  Created on: Jan 1, 2020
 *      Author: jan
 */
// ***** 1. Pre-processor Directives Section *****
#include <stdint.h>
#include <stdbool.h>
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/uart.h"
#include "inc/hw_memmap.h"
#include "driverlib/pin_map.h"


//*************************************************************
// Configures the UART on PA0 and PA1 to
// use the COM port for transferring data to the PC
// Input: n.a.
// Output: n.a.
// Notes: clock is based on the PLL @ 80MHz
// Sets the COM to:
// 115200 bps, use 8 bit, no parity, and 1 stop bit
void ConfigureUART0(void)
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
    UARTConfigSetExpClk(UART0_BASE, 80000000, 115200,
                                (UART_CONFIG_PAR_NONE | UART_CONFIG_STOP_ONE |
                                 UART_CONFIG_WLEN_8));

}
