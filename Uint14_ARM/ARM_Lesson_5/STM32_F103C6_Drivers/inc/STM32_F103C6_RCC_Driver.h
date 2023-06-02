/*
 * STM32_F103C6_RCC_Driver.h
 *
 *  Created on: Nov 29, 2022
 *      Author: Guirguis
 */

#ifndef INC_STM32_F103C6_RCC_DRIVER_H_
#define INC_STM32_F103C6_RCC_DRIVER_H_

#include "stm32f103x6.h"

uint32_t MCAL_RCC_Get_SYSFreq(void) ;
uint32_t MCAL_RCC_Get_HCLKFreq(void) ;
uint32_t MCAL_RCC_Get_PCLK1Freq(void);
uint32_t MCAL_RCC_Get_PCLK2Freq(void);


#define HSE_Clock	 	(uint32_t)16000000
#define HSI_RC_CLK		(uint32_t)8000000

#endif /* INC_STM32_F103C6_RCC_DRIVER_H_ */
