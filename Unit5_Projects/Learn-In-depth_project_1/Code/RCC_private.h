/********************************************************************************/
/* Author 			: Guirguis Hedia 											*/
/* Date 			: 20 Feb 2023												*/
/* Version 			: V01														*/
/********************************************************************************/


#ifndef RCC_PRIVATE_H
#define RCC_PRIVATE_H

/* Register Definitions */

#define RCC_CR					*((volatile u32*) 0x40021000)
#define RCC_CFGR				*((volatile u32*) 0x40021004)
#define RCC_CIR					*((volatile u32*) 0x40021008)
#define RCC_APB2RSTR			*((volatile u32*) 0x4002100C)
#define RCC_APB1RSTR			*((volatile u32*) 0x40021010)
#define RCC_AHBENR				*((volatile u32*) 0x40021014)
#define RCC_APB2ENR				*((volatile u32*) 0x40021018)
#define RCC_APB1ENR				*((volatile u32*) 0x4002101C)
#define RCC_BDCR				*((volatile u32*) 0x40021020)
#define RCC_CSR					*((volatile u32*) 0x40021024)
#define RCC_AHBSTR				*((volatile u32*) 0x40021028)
#define RCC_CFGR2				*((volatile u32*) 0x4002102C)



/********************************************************************************/
/*				THis part for Configuration for RCC System CLK 														*/
/********************************************************************************/

#define RCC_HSI_CLK				0
#define RCC_HSE_CLK				1
#define RCC_PLL_CLK				2

/********************************************************************************/
/********************************************************************************/


/********************************************************************************/
/*				THis part for Configuration RCC External CLK Freq				*/
/*NOTES :		OUR Choice in MHz
				OUR Range form RCC_HSE_4MHZ to RCC_HSE_16MHZ													*/
/********************************************************************************/
#define RCC_HSE_4MHZ	4
#define RCC_HSE_5MHZ	5
#define RCC_HSE_6MHZ	6
#define RCC_HSE_7MHZ	7
#define RCC_HSE_8MHZ	8
#define RCC_HSE_9MHZ	9
#define RCC_HSE_10MHZ	10
#define RCC_HSE_11MHZ	11
#define RCC_HSE_12MHZ	12
#define RCC_HSE_13MHZ	13
#define RCC_HSE_14MHZ	14
#define RCC_HSE_15MHZ	15
#define RCC_HSE_16MHZ	16

#define RCC_HSE_OSCI		0
#define RCC_HSE_RC			1

/********************************************************************************/
/********************************************************************************/



/********************************************************************************/
/*				THis part for Configuration for MCO OUTPUT pin 														*/
/********************************************************************************/

#define RCC_MCO_NO_CLK	0
#define RCC_MCO_SYSCLK	1
#define RCC_MCO_HSI		2
#define RCC_MCO_HSE		3
#define RCC_MCO_PLLCLK	4
/********************************************************************************/
/********************************************************************************/

#endif
