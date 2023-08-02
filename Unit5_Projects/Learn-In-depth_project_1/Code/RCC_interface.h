/********************************************************************************/
/* Author 			: Guirguis Hedia 											*/
/* Date 			: 20 Feb 2023												*/
/* Version 			: V02														*/
/********************************************************************************/


#ifndef RCC_INTERFACE_H
#define RCC_INTERFACE_H

#include "STD_TYPES.h"
#include "BIT_MATH.h"

typedef enum {
	RCC_OK,
	RCC_ERROR_CHOOSE_SOURCE,
	
	RCC_HSI_RDY,
	RCC_HSI_NOT_RDY,
	RCC_HSE_RDY,
	RCC_HSE_NOT_RDY,
	RCC_PLL_RDY,
	RCC_PLL_NOT_RDY,
	
	RCC_HSE_ERROR_CHOOSE_SOURCE
}RCC_error;


				/*Option for Copy_u8BusId*/

#define 	RCC_AHB									0
#define 	RCC_APB1								1
#define 	RCC_APB2								2


				/*Option for Copy_u8PerId*/
						/*AHB Bus*/
#define 	RCC_AHB_DMA1								0
#define 	RCC_AHB_DMA2								1
#define 	RCC_AHB_SRAM								2
#define 	RCC_AHB_FLITF								4
#define 	RCC_AHB_CRC									6
#define 	RCC_AHB_OTGFS								12
#define 	RCC_AHB_ETHMA								14
#define 	RCC_AHB_ETHMAC_TX							15
#define 	RCC_AHB_ETHMAC_RX							16




					/*Option for Copy_u8PerId*/
							/*APB2 Bus*/
#define 	RCC_APB2_AFIO								0
#define 	RCC_APB2_IOPA								2
#define 	RCC_APB2_IOPB								3
#define 	RCC_APB2_IOPC								4
#define 	RCC_APB2_IOPD								5
#define 	RCC_APB2_IOPE								6
#define 	RCC_APB2_ADC1								9
#define 	RCC_APB2_ADC2								10
#define 	RCC_APB2_TIM1								11
#define 	RCC_APB2_SPI1								12
#define 	RCC_APB2_USART1								14



					/*Option for Copy_u8PerId*/
							/*APB2 Bus*/
#define 	RCC_APB1_TIM2								0
#define 	RCC_APB1_TIM3								1
#define 	RCC_APB1_TIM4								2
#define 	RCC_APB1_TIM5								3
#define 	RCC_APB1_TIM6								4
#define 	RCC_APB1_TIM7								5
#define 	RCC_APB1_WWDG								11
#define 	RCC_APB1_SPI2								14
#define 	RCC_APB1_SPI3								15
#define 	RCC_APB1_USART2								17
#define 	RCC_APB1_USART3								18
#define 	RCC_APB1_USART4								19
#define 	RCC_APB1_USART5								20
#define 	RCC_APB1_I2C1								21
#define 	RCC_APB1_I2C2								22
#define 	RCC_APB1_CAN1								25
#define 	RCC_APB1_CAN2								26
#define 	RCC_APB1_BKP								27
#define 	RCC_APB1_PWR								28
#define 	RCC_APB1_DAC								29



 
void RCC_u8EnableClock(u8 Copy_u8BusId,u8 Copy_u8PerId);

void RCC_u8DisableClock(u8 Copy_u8BusId,u8 Copy_u8PerId);

void RCC_voidInitSystemClk(void);

#endif
