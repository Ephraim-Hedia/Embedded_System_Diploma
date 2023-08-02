/********************************************************************************/
/* Author 			: Guirguis Hedia 											*/
/* Date 			: 20 Feb 2023												*/
/* Version 			: V01														*/
/********************************************************************************/


#ifndef RCC_CONFIG_H
#define RCC_CONFIG_H

/********************************************************************************/
/*				THis part for Configuration for RCC CLK ENABLE
 * NOTES:		Comment the Clock you don't want to Enable it  														*/
/********************************************************************************/

#define RCC_HSI_ENABLE	0
//#define RCC_HSE_ENABLE	1
//#define RCC_PLL_ENABLE	0


/********************************************************************************/
/*				This part for Configuration for RCC System CLK
/********************************************************************************/
/*
 * Options :	RCC_HSI_CLK
 * 				RCC_HSE_CLK
 * 				RCC_PLL_CLK
/********************************************************************************/
/********************   Choose YOUR Choice From Above Option	*****************/
/********************************************************************************/
#define SYSTEM_CLK_SOURCE 		RCC_HSI_CLK



/********************************************************************************/
/*				THis part for Configuration RCC Internal CLK Freq				*/
/*NOTES :		This part Only for Improve INternal Oscillator by trimming
				This Function in STM32																*/
/********************************************************************************/
/********************   Choose YOUR Choice From Above Option	*****************/
/********************************************************************************/

#if(SYSTEM_CLK_SOURCE == RCC_HSI_CLK)
	#define RCC_HSI_Trimming	(unsigned char)16		
#endif



/********************************************************************************/
/*				THis part for Configuration RCC External CLK Freq				*/
/********************************************************************************/
/*NOTES :		You should Input Your External CLK Freq
 Options:		-RCC_HSE_4MHZ - RCC_HSE_16MHZ --> for RCC_HSE_CLK_FERQ
 	 	 	 	-RCC_HSE_OSCI,RCC_HSE_RC			 for RCC_HSE_CLK_OSCI
/********************************************************************************/
/********************   Choose Your Choice From Above Option	*****************/
/********************************************************************************/

#if(SYSTEM_CLK_SOURCE == RCC_HSE_CLK) 
	#define	 	RCC_HSE_CLK_FERQ	RCC_HSE_4MHZ
	#define 	RCC_HSE_CLK_OSCI	RCC_HSE_OSCI
#endif


/********************************************************************************/
/*				THis part for Configuration for MCO OUTPUT pin
/********************************************************************************/
/* Options  :	RCC_MCO_NO_CLK
 * 				RCC_MCO_SYSCLK
 * 				RCC_MCO_HSI
 * 				RCC_MCO_HSE
 * 				RCC_MCO_PLLCLK													*/
/********************************************************************************/
/********************   Choose Your Choice From Above Option	*****************/
/********************************************************************************/
#define RCC_MCO_SOURCE	RCC_MCO_NO_CLK



#endif
