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
#include "PLL.h"
#include "hw_memmap.h"
// test
// hier wordt een unsigned long HEX getal eerst uitgerekend en daarna omgezet naar een pointer!
#define SW1                     (*((volatile unsigned long *)(GPIO_PORTF_BASE + (0x10 << 2)))) //SW1 on PF4
#define SW1_address             ((volatile unsigned long *)(GPIO_PORTF_BASE + (0x10 << 2)))

#define Blue_LED                (*((volatile unsigned long *)(GPIO_PORTF_BASE + (0x04 << 2)))) //blue LED on PF2
#define Blue_LED_address         ((volatile unsigned long *)(GPIO_PORTF_BASE + (0x04 << 2)))

// hier is GPIO_PORTF_DATA_BITS_R al een pointer en vindt er pointer arithmetic plaats
#define PF4                     ((*(GPIO_PORTF_DATA_BITS_R + (1 << 4))) >> 4)
#define PF4_address             (GPIO_PORTF_DATA_BITS_R + (1 << 4))

// function prototype
void Init_PF(void);
void Delay100ms(unsigned long);

// basic functions defined at end of startup.s
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts

int main(void)
{
    unsigned long volatile delay;
    volatile unsigned long *sw1address = SW1_address;
    volatile unsigned long *blueledaddress = Blue_LED_address;
    volatile uint32_t *pf4address = PF4_address;

    PLL_Init(); // set system clock to 80 MHz
    // initialization goes here
    Init_PF();

    Blue_LED = 0x04;                          // turn blue LED on PF2
    while (1)
    {
        // body goes here
        if (!(SW1 & 0x10))
        {                       // if SW is pressed (negative logic)
            Blue_LED ^= 0x04;                   // toggle Blue_LED
            Delay100ms(4);                      // delay toggle
        }
        else
            Blue_LED = 0x04;                    // turn blue LED on PF2
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
    volatile unsigned long delay;
    SYSCTL_RCGC2_R |= 0x00000020;   // 1) F clock
    delay = SYSCTL_RCGC2_R;         // delay to allow clock to stabilize
    GPIO_PORTF_AMSEL_R &= 0x00;     // 2) disable analog function
    GPIO_PORTF_PCTL_R &= ~0x000F0F00;   // 3) GPIO clear bit PCTL PF4 and PF2
    GPIO_PORTF_DIR_R &= ~0x10;      // 4.1) PF4 input,
    GPIO_PORTF_DIR_R |= 0x04;       // 4.2) PF2 output
    GPIO_PORTF_AFSEL_R &= 0x00;     // 5) no alternate function
    GPIO_PORTF_PUR_R |= 0x10;       // 6) enable pullup resistor on PF4 (negative logic)
    GPIO_PORTF_DEN_R |= 0x14;       // 7) enable digital pins PF4 and PF2
}
