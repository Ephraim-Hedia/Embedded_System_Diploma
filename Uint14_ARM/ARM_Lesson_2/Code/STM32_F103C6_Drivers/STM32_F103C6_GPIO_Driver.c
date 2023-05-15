/*
 * STM32_F103C6_GPIO_Driver.c
 *
 *  Created on: Oct 23, 2022
 *      Author: Guirguis Hedia
 */
#include "STM32_F103C6_GPIO_Driver.h"

uint8_t Get_CRLH_Position (uint16_t PinNumber)
{
	switch (PinNumber)
	{
	//CRL Register Bit Position
	case GPIO_PIN_0:
		return 0;
		break;
	case GPIO_PIN_1:
		return 4;
		break;
	case GPIO_PIN_2:
		return 8;
		break;
	case GPIO_PIN_3:
		return 12;
		break;
	case GPIO_PIN_4:
		return 16;
		break;
	case GPIO_PIN_5:
		return 20;
		break;
	case GPIO_PIN_6:
		return 24;
		break;
	case GPIO_PIN_7:
		return 28;
		break;

		//CRH Register Bit Position
	case GPIO_PIN_8:
		return 0;
		break;
	case GPIO_PIN_9:
		return 4;
		break;
	case GPIO_PIN_10:
		return 8;
		break;
	case GPIO_PIN_11:
		return 12;
		break;
	case GPIO_PIN_12:
		return 16;
		break;
	case GPIO_PIN_13:
		return 20;
		break;
	case GPIO_PIN_14:
		return 24;
		break;
	case GPIO_PIN_15:
		return 28;
		break;
	}
	return 0;
}
/**================================================================
 * @Fn				-MCAL_GPIO_Init
 * @brief		    -Initialize The GPIOx PINy according to The specific parameters in The Pinconfig
 * @param[in]	 	-GPIOx:where x can be (A..E depending on device used) to select the GPIO peripheral
 * @param[in] 		-PinConfig : pointer to a GPIO_PinConfig_t structure that contains
 *					 the configuration information for the specific GPIO peripheral
 * @retval			-none
 * Note				-STM32f103c6 MCU has GPIO A,B,C,D,E Modules
 * 					 but LQFP48 Package has only GPIO A,B,Part of C,D exported as external
 */
void MCAL_GPIO_Init(GPIO_TypeDef * GPIOx , GPIO_PinConfig_t* PinConfig)
{


	//Port configuration register low (GPIOx_CRL) --> Configure Pins form 0:7
	//Port configuration register HIGH (GPIOx_CRH) --> Configure Pins form 8:15

	volatile uint32_t *configregister =NULL;
	uint8_t PIN_Config = 0 ;
	configregister= (PinConfig->GPIO_PinNumber < GPIO_PIN_8 )? &GPIOx->CRL : &GPIOx->CRH  ;

	//Clear MODEx[0:1] CNFx[0:1]
	(*configregister) &=~ (0xf << Get_CRLH_Position(PinConfig->GPIO_PinNumber));

	//if PIN is OUTPUT
	if((PinConfig->GPIO_Mode == GPIO_MODE_OUTPUT_PP)||(PinConfig->GPIO_Mode == GPIO_MODE_OUTPUT_OD)||(PinConfig->GPIO_Mode == GPIO_MODE_OUTPUT_AF_PP)||(PinConfig->GPIO_Mode == GPIO_MODE_OUTPUT_AF_OD))
	{
		//Set MODEx[0:1] CNFx[0:1]
		PIN_Config = ( (((PinConfig->GPIO_Mode -4 )<<2) | PinConfig->GPIO_Output_Speed) & 0xf) ;
	}
	// if Input Mode
	else  //MODE = 00 : input mode (reset state)
	{
		if(PinConfig->GPIO_Mode==GPIO_MODE_INPUT_FLO || PinConfig->GPIO_Mode == GPIO_MODE_Analog)
		{
			//Set MODEx[0:1]-->00 & CNFx[0:1]
			PIN_Config = ( (((PinConfig->GPIO_Mode) << 2 ) | 0x0 )& 0xf);

		}else if (PinConfig->GPIO_Mode==GPIO_MODE_AF_INPUT) //Consider it as input Floating
		{
			//Set MODEx[0:1]-->00 & CNFx[0:1]
			PIN_Config = ( (((GPIO_MODE_INPUT_FLO) << 2 ) | 0x0 )& 0xf);
		}
		else //PU PD Input
		{
			//Set MODEx[0:1]-->00 & CNFx[0:1]
			PIN_Config = ( (((GPIO_MODE_INPUT_PU) << 2 ) | 0x0 )& 0xf);
			if(PinConfig->GPIO_Mode == GPIO_MODE_INPUT_PU)
			{
				//				Table 20. Port bit configuration table PxODR=1
				GPIOx->ODR |= PinConfig->GPIO_PinNumber;

			}else
			{
				GPIOx->ODR &=~ PinConfig->GPIO_PinNumber;
			}
		}
	}
	//Write on CRL or CRH Register To Select Mode and Speed
	(*configregister) |= (PIN_Config << Get_CRLH_Position(PinConfig->GPIO_PinNumber));
}


/**================================================================
 * @Fn				-MCAL_GPIO_DeInit
 * @brief		    -Reset all GPIO registers
 * @param[in]	 	-GPIOx:where x can be (A..E depending on device used) to select the GPIO peripheral
 * @retval			-none
 * Note				-none
 *
 */
void MCAL_GPIO_DeInit(GPIO_TypeDef * GPIOx)
{

	//Manual Way To Reset Registers
	//	GPIOx->BRR = 0x00000000;
	//	GPIOx->BSRR= 0x00000000;
	//	GPIOx->CRH = 0x44444444;
	//	GPIOx->CRL = 0x44444444;
	////	GPIOx->IDR  --> READ ONLY
	//	GPIOx->LCKR = 0x00000000;
	//	GPIOx->ODR = 0x00000000;

	//or you can use the reset Controller
	//APB2 Peripheral reset register (RCC_APB2RSTR)
	//SET and Cleared by Software
	if(GPIOx==GPIOA)
	{
		RCC->APB2RSTR |=(1<<2); //Bit 2 IOPARST
		RCC->APB2RSTR &=~ (1<<2);
	}else if (GPIOx==GPIOB)
	{
		RCC->APB2RSTR |=(1<<3); //Bit 3 IOPBRST
		RCC->APB2RSTR &=~ (1<<3);
	}else if (GPIOx==GPIOC)
	{
		RCC->APB2RSTR |=(1<<4); //Bit 4 IOPCRST
		RCC->APB2RSTR &=~ (1<<4);
	}else if (GPIOx==GPIOD)
	{
		RCC->APB2RSTR |=(1<<5); //Bit 5 IOPDRST
		RCC->APB2RSTR &=~ (1<<5);
	}
}



/**================================================================
 * @Fn				-MCAL_GPIO_ReadPin
 * @brief		    -Read Specific PIN
 * @param[in]	 	-GPIOx:where x can be (A..E depending on device used) to select the GPIO peripheral
 * @param[in]		-PinNumber: Set Pin Number according @ref GPIO_PINS_define
 * @retval			-The input pin Value (Two Value based on @ref GPIO_PIN_State)
 * Note				-none
 */
uint8_t MCAL_GPIO_ReadPin(GPIO_TypeDef * GPIOx,uint16_t PinNumber)
{
	uint8_t bitstatus;
	if((GPIOx->IDR & PinNumber )!= (uint32_t)GPIO_PIN_RESET)
	{
		bitstatus= GPIO_PIN_SET;
	}
	else
	{
		bitstatus= GPIO_PIN_RESET;
	}
	return bitstatus;
}


/**================================================================
 * @Fn				-MCAL_GPIO_ReadPort
 * @brief		    -Read The input Port VAlue
 * @param[in]	 	-GPIOx:where x can be (A..E depending on device used) to select the GPIO peripheral
 * @retval			-The input port Value
 * Note				-none
 */
uint16_t MCAL_GPIO_ReadPort(GPIO_TypeDef * GPIOx)
{
	uint16_t portvalue;
	portvalue=(uint16_t) GPIOx->IDR;
	return portvalue;
}

/**================================================================
 * @Fn				-MCAL_GPIO_WritePin
 * @brief		    -Write Specific PIN
 * @param[in]	 	-GPIOx:where x can be (A..E depending on device used) to select the GPIO peripheral
 * @param[in]		-PinNumber: Set Pin Number according @ref GPIO_PINS_define
 * @param[in]		-Value: pin Value
 * @retval			-none
 * Note				-none
 */
void MCAL_GPIO_WritePin(GPIO_TypeDef * GPIOx,uint16_t PinNumber ,uint8_t Value)
{
	if(Value != (uint8_t)GPIO_PIN_RESET)
	{
		//		GPIOx->ODR |= PinNumber;
		//		or
		GPIOx->BSRR= (uint32_t)PinNumber;
	}
	else
	{
		//		GPIOx->ODR &=~ PinNumber;
		//		or
		//		GPIOx->BSRR=(PinNumber << 16);
		//		or
		GPIOx->BRR=(uint32_t)PinNumber;
	}
}

/**================================================================
 * @Fn				-MCAL_GPIO_WritePort
 * @brief		    -Write on output port
 * @param[in]	 	-GPIOx:where x can be (A..E depending on device used) to select the GPIO peripheral
 * @param[in]		-Value: pin Value
 * @retval			-none
 * Note				-none
 *
 */
void MCAL_GPIO_WritePort(GPIO_TypeDef * GPIOx ,uint16_t Value)
{
	GPIOx->ODR =(uint32_t)Value;
}


/**================================================================
 * @Fn				-MCAL_GPIO_TogglePin
 * @brief		    -Toggle pin
 * @param[in]	 	-GPIOx:where x can be (A..E depending on device used) to select the GPIO peripheral
 * @param[in]		-PinNumber: Set Pin Number according @ref GPIO_PINS_define
 * @retval			-none
 * Note				-none
 *
 */
void MCAL_GPIO_TogglePin(GPIO_TypeDef * GPIOx,uint16_t PinNumber)
{
	GPIOx->ODR ^= PinNumber;
}

/**================================================================
 * @Fn				-MCAL_GPIO_WriteByte
 * @brief		    -Write in specific Byte
 * @param[in]	 	-GPIOx:where x can be (A..E depending on device used) to select the GPIO peripheral
 * @param[in]		-GPIO_Byte_Number: Set Pin Number according @ref GPIO_Byte_Number_define
 * @retval			-none
 * Note				-none
 *
 */

void MCAL_GPIO_WriteByte(GPIO_TypeDef * GPIOx ,uint8_t GPIO_Byte_Number,uint8_t Value)
{
	if(GPIO_Byte_Number==GPIO_FIRST_BYTE)
	{
		GPIOx->ODR &= 0xFF00;
		GPIOx->ODR |=(uint8_t)Value;
	}
	else if(GPIO_Byte_Number==GPIO_SECOND_BYTE)
	{
		GPIOx->ODR &= 0x00FF;
		GPIOx->ODR |=((uint8_t)Value<<8);
	}
}

/**================================================================
 * @Fn				-MCAL_GPIO_Write_Nibble
 * @brief		    -Write in specific Nibble
 * @param[in]	 	-GPIOx:where x can be (A..E depending on device used) to select the GPIO peripheral
 * @param[in]		-GPIO_Byte_Number: Set Pin Number according @ref GPIO_Nibble_Number_define
 * @retval			-none
 * Note				-none
 *
 */

void MCAL_GPIO_Write_Nibble(GPIO_TypeDef * GPIOx ,uint8_t GPIO_Nibble_Number,uint8_t Value)
{
	if(GPIO_Nibble_Number==GPIO_FIRST_NIBBLE)
	{
		Value =Value & 0x0f;
		GPIOx->ODR &= 0xFFF0;
		GPIOx->ODR |=(uint8_t)Value;
	}
	else if(GPIO_Nibble_Number==GPIO_SECOND_NIBBLE)
	{
		Value =Value & 0x0f;
		GPIOx->ODR &= 0xFF0F;
		GPIOx->ODR |=((uint8_t)Value<<4);
	}
	else if(GPIO_Nibble_Number==GPIO_THIRD_NIBBLE)
	{
		Value =Value & 0x0f;
		GPIOx->ODR &= 0xF0FF;
		GPIOx->ODR |=((uint8_t)Value<<8);
	}
	else if(GPIO_Nibble_Number==GPIO_FOURTH_NIBBLE)
	{
		Value =Value & 0x0f;
		GPIOx->ODR &= 0x0FFF;
		GPIOx->ODR |=((uint8_t)Value<<12);
	}
}

/**================================================================
 * @Fn				-MCAL_GPIO_LockPin
 * @brief		    -The locking Mechanism allows the IO configuration to be frozen
 * @param[in]	 	-GPIOx:where x can be (A..E depending on device used) to select the GPIO peripheral
 * @param[in]		-PinNumber: Set Pin Number according @ref GPIO_PINS_define
 * @retval			-OK if The pin Config is locked or ERROR if Pin not Locked (OK & ERROR are defined @ref GPIO_RETURN_LOCK)
 * Note				-none
 */

uint8_t MCAL_GPIO_LockPin(GPIO_TypeDef * GPIOx,uint16_t PinNumber)
{
	//	Bit 16 LCKK[16]: Lock key
	//	This bit can be read anytime. It can only be modified using the Lock Key Writing Sequence.
	//	0: Port configuration lock key not active
	//	1: Port configuration lock key active. GPIOx_LCKR register is locked until the next reset.
	//	LOCK key writing sequence:
	//	Write 1
	//	Write 0
	//	Write 1
	//	Read 0
	//	Read 1 (this read is optional but confirms that the lock is active)
	//	Note: During the LOCK Key Writing sequence, the value of LCK[15:0] must not change.
	//	Any error in the lock sequence will abort the lock.
	//	Bits 15:0 LCKy: Port x Lock bit y (y= 0 .. 15)
	//	These bits are read write but can only be written when the LCKK bit is 0.
	//	0: Port configuration not locked
	//	1: Port configuration locked.

	//Set LCKK[16]
	volatile uint32_t tmp =1<<16;
	//Set LCKy
	tmp |= PinNumber;

	//	Write 1
	GPIOx->LCKR =tmp;
	//	Write 0
	GPIOx->LCKR =PinNumber;
	//	Write 1
	GPIOx->LCKR =tmp;
	//	Read 0
	tmp =GPIOx->LCKR;
	//	Read 1 (this read is optional but confirms that the lock is active)
	if((uint32_t)(GPIOx->LCKR & 1<<16))
	{
		return GPIO_RETURN_LOCK_OK;
	}
	else
	{
		return GPIO_RETURN_LOCK_ERROR;
	}

}



