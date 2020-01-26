/*
 * PLL.h
 *
 *  Created on: 21 sep. 2019
 *      Author: Jan
 */

#ifndef PLL_H_
#define PLL_H_

// The #define statement SYSDIV2 initializes
// the PLL to the desired frequency.
#define SYSDIV2 4
// bus frequency is 400MHz/(SYSDIV2+1) = 400MHz/(4+1) = 80 MHz

// configure the system to get its clock from the PLL
void PLL_Init(void);



#endif /* PLL_H_ */
