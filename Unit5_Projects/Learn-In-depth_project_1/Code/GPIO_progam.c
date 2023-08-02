/********************************************************************************/
/* Author 			: Guirguis Hedia 											*/
/* Date 			: 27 Feb 2023												*/
/* Version 			: V01														*/
/********************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "GPIO_interface.h"
#include "GPIO_private.h"
#include "GPIO_config.h"



void MGPIO_voidSetPinDir(u8 Copy_u8PortId,u8 Copy_u8PinId,u8 Copy_u8PinMode)
{
	switch (Copy_u8PortId)
	{
	case GPIOA:
		if(Copy_u8PinId <=7)
		{
			//Clear The Pins Before Put the VAlue
			GPIOA_CRL &=~ (u32)(0b1111<< (Copy_u8PinId*4));
			//Put The Value in the register
			GPIOA_CRL |= (u32)(Copy_u8PinMode<< (Copy_u8PinId*4));
		}
		else if (Copy_u8PinId <=15)
		{
			//Clear The Pins Before Put the VAlue
			GPIOA_CRH &=~ (u32)(0b1111<< ((Copy_u8PinId-8)*4));
			//Put The Value in the register
			GPIOA_CRH |= (u32)(Copy_u8PinMode<< ((Copy_u8PinId-8)*4));
		}
		else
		{

		}
		break;
	case GPIOB:
		if(Copy_u8PinId <=7)
		{
			//Clear The Pins Before Put the VAlue
			GPIOB_CRL &=~(0b1111<< (Copy_u8PinId*4));
			//Put The Value in the register
			GPIOB_CRL |=(Copy_u8PinMode<< (Copy_u8PinId*4));
		}
		else if (Copy_u8PinId <=15)
		{
			//Clear The Pins Before Put the VAlue
			GPIOB_CRH &=~(0b1111<< ((Copy_u8PinId-8)*4));
			//Put The Value in the register
			GPIOB_CRH |=(Copy_u8PinMode<< ((Copy_u8PinId-8)*4));
		}
		else
		{

		}
		break;
	case GPIOC:
		if(Copy_u8PinId <=7)
		{
			//Clear The Pins Before Put the VAlue
			GPIOC_CRL &=~(0b1111<< (Copy_u8PinId*4));
			//Put The Value in the register
			GPIOC_CRL |=(Copy_u8PinMode<< (Copy_u8PinId*4));
		}
		else if (Copy_u8PinId <=15)
		{
			//Clear The Pins Before Put the VAlue
			GPIOC_CRH &=~(0b1111<< ((Copy_u8PinId-8)*4));
			//Put The Value in the register
			GPIOC_CRH |=(Copy_u8PinMode<< ((Copy_u8PinId-8)*4));
		}
		else
		{

		}
		break;
	default:
		break;

	}
	//	GPIOA_CRL =2;
}


void MGPIO_voidSetPinVal(u8 Copy_u8PortId,u8 Copy_u8PinId,u8 Copy_u8PinVal)
{
	switch (Copy_u8PortId)
	{
	case GPIOA:
		if(Copy_u8PinVal == GPIO_HIGH) 			SET_BIT(GPIOA_ODR,Copy_u8PinId);
		else if(Copy_u8PinVal == GPIO_LOW)		CLR_BIT(GPIOA_ODR,Copy_u8PinId);
		break;
	case GPIOB :
		if(Copy_u8PinVal == GPIO_HIGH) 			SET_BIT(GPIOB_ODR,Copy_u8PinId);
		else if(Copy_u8PinVal == GPIO_LOW)		CLR_BIT(GPIOB_ODR,Copy_u8PinId);
		break;
	case GPIOC :
		if(Copy_u8PinVal == GPIO_HIGH) 			SET_BIT(GPIOC_ODR,Copy_u8PinId);
		else if(Copy_u8PinVal == GPIO_LOW)		CLR_BIT(GPIOC_ODR,Copy_u8PinId);
		break;
	default :
		break;
	}

	//	GPIOA_ODR |=(1<<0);

}


u16 MGPIO_voidGetPinVal(u8 Copy_u8PortId,u8 Copy_u8PinId)
{
	u16 result ;
	switch (Copy_u8PortId)
	{
	case GPIOA:
		result = GET_BIT(GPIOA_IDR,Copy_u8PinId);
		break;
	case GPIOB :
		result = GET_BIT(GPIOB_IDR,Copy_u8PinId);
		break;
	case GPIOC :
		result = GET_BIT(GPIOC_IDR,Copy_u8PinId);
		break;
	default :
		break;
	}
	return result ;

}





void MGPIO_voidSetByteDir(u8 Copy_u8PortId,u8 Copy_BytePosition,u32 Copy_u8ByteDir)
{
	switch (Copy_u8PortId)
	{
	case GPIOA:
		if(Copy_BytePosition==GPIO_BYTE_POSITION_LOW)
		{
			GPIOA_CRL = Copy_u8ByteDir;
		}
		else if (Copy_BytePosition==GPIO_BYTE_POSITION_HIGH)
		{
			GPIOA_CRH = Copy_u8ByteDir;
		}
		else{}
		break;
	case GPIOB:
		if(Copy_BytePosition==GPIO_BYTE_POSITION_LOW)
		{
			GPIOB_CRL = Copy_u8ByteDir;
		}
		else if (Copy_BytePosition==GPIO_BYTE_POSITION_HIGH)
		{
			GPIOB_CRH = Copy_u8ByteDir;
		}
		else{}
		break;
	case GPIOC:
		if(Copy_BytePosition==GPIO_BYTE_POSITION_LOW)
		{
			GPIOC_CRL = Copy_u8ByteDir;
		}
		else if (Copy_BytePosition==GPIO_BYTE_POSITION_HIGH)
		{
			GPIOC_CRH = Copy_u8ByteDir;
		}
		else{}
		break;
	default :break;
	}

}

void MGPIO_voidSetByteVal(u8 Copy_u8PortId,u8 Copy_BytePosition,u8 Copy_u8ByteVal)
{
	switch (Copy_u8PortId)
	{
	case GPIOA:
		if(Copy_BytePosition == GPIO_BYTE_POSITION_LOW)
		{
			GPIOA_ODR &=~(0x000000FF);
			GPIOA_ODR |=(Copy_u8ByteVal);
		}
		else if(Copy_BytePosition == GPIO_BYTE_POSITION_HIGH)
		{
			GPIOA_ODR &=~(0x0000FF00);
			GPIOA_ODR |=(Copy_u8ByteVal<<8);

		}
		else{}
		break;
	case GPIOB:
		if(Copy_BytePosition == GPIO_BYTE_POSITION_LOW)
		{
			GPIOB_ODR &=~(0x000000FF);
			GPIOB_ODR |=(Copy_u8ByteVal);
		}
		else if(Copy_BytePosition == GPIO_BYTE_POSITION_HIGH)
		{
			GPIOB_ODR &=~(0x0000FF00);
			GPIOB_ODR |=(Copy_u8ByteVal<<8);

		}
		else{}
		break;
	case GPIOC:
		if(Copy_BytePosition == GPIO_BYTE_POSITION_LOW)
		{
			GPIOC_ODR &=~(0x000000FF);
			GPIOC_ODR |=(Copy_u8ByteVal);
		}
		else if(Copy_BytePosition == GPIO_BYTE_POSITION_HIGH)
		{
			GPIOC_ODR &=~(0x0000FF00);
			GPIOC_ODR |=(Copy_u8ByteVal<<8);
		}
		else{}
		break;
	default :break;
	}
}



void MGPIO_voidTogglePin(u8 Copy_u8PortId,u8 Copy_u8PinId)
{
	switch (Copy_u8PortId)
	{
	case GPIOA:
		TOG_BIT(GPIOA_ODR,Copy_u8PinId);
		break;
	case GPIOB:
		TOG_BIT(GPIOB_ODR,Copy_u8PinId);
		break;
	case GPIOC:
		TOG_BIT(GPIOC_ODR,Copy_u8PinId);
		break;
	default :
		break;
	}
}



void MGPIO_voidSetNibbleDir(u8 Copy_u8PortId,u8 Copy_NibblePosition,u16 Copy_u8NibbleDir)
{
	switch (Copy_u8PortId)
	{
	case GPIOA:
		if(Copy_NibblePosition == GPIO_NIBBLE_LOW_BYTE_LOW)
		{

			GPIOA_CRL &=~(0x0000FFFF);
			GPIOA_CRL |=(Copy_u8NibbleDir);
		}
		else if(Copy_NibblePosition == GPIO_NIBBLE_HIGH_BYTE_LOW)
		{
			GPIOA_CRL &=~(0xFFFF0000);
			GPIOA_CRL |=(Copy_u8NibbleDir<<16);

		}
		else if(Copy_NibblePosition == GPIO_NIBBLE_LOW_BYTE_HIGH)
		{
			GPIOA_CRH &=~(0x0000FFFF);
			GPIOA_CRH |=(Copy_u8NibbleDir);

		}
		else if(Copy_NibblePosition == GPIO_NIBBLE_HIGH_BYTE_HIGH)
		{
			GPIOA_CRH &=~(0xFFFF0000);
			GPIOA_CRH |=(Copy_u8NibbleDir<<16);

		}
		else{}
		break;
	case GPIOB:
		if(Copy_NibblePosition == GPIO_NIBBLE_LOW_BYTE_LOW)
		{

			GPIOB_CRL &=~(0x0000FFFF);
			GPIOB_CRL |=(Copy_u8NibbleDir);
		}
		else if(Copy_NibblePosition == GPIO_NIBBLE_HIGH_BYTE_LOW)
		{
			GPIOB_CRL &=~(0xFFFF0000);
			GPIOB_CRL |=(Copy_u8NibbleDir<<16);

		}
		else if(Copy_NibblePosition == GPIO_NIBBLE_LOW_BYTE_HIGH)
		{
			GPIOB_CRH &=~(0x0000FFFF);
			GPIOB_CRH |=(Copy_u8NibbleDir);

		}
		else if(Copy_NibblePosition == GPIO_NIBBLE_HIGH_BYTE_HIGH)
		{
			GPIOB_CRH &=~(0xFFFF0000);
			GPIOB_CRH |=(Copy_u8NibbleDir<<16);

		}
		else{}
		break;
	case GPIOC:
		if(Copy_NibblePosition == GPIO_NIBBLE_LOW_BYTE_LOW)
		{

			GPIOC_CRL &=~(0x0000FFFF);
			GPIOC_CRL |=(Copy_u8NibbleDir);
		}
		else if(Copy_NibblePosition == GPIO_NIBBLE_HIGH_BYTE_LOW)
		{
			GPIOC_CRL &=~(0xFFFF0000);
			GPIOC_CRL |=(Copy_u8NibbleDir<<16);

		}
		else if(Copy_NibblePosition == GPIO_NIBBLE_LOW_BYTE_HIGH)
		{
			GPIOC_CRH &=~(0x0000FFFF);
			GPIOC_CRH |=(Copy_u8NibbleDir);

		}
		else if(Copy_NibblePosition == GPIO_NIBBLE_HIGH_BYTE_HIGH)
		{
			GPIOC_CRH &=~(0xFFFF0000);
			GPIOC_CRH |=(Copy_u8NibbleDir<<16);

		}
		else{}
		break;
	default :break;
	}
}

void MGPIO_voidSetNibbleVal(u8 Copy_u8PortId,u8 Copy_NibblePosition,u8 Copy_u8NibbleVal)
{
	switch (Copy_u8PortId)
	{
	case GPIOA:
		if(Copy_NibblePosition == GPIO_NIBBLE_LOW_BYTE_LOW)
		{

			GPIOA_ODR &=~(0x0000000F);
			GPIOA_ODR |=(Copy_u8NibbleVal);
		}
		else if(Copy_NibblePosition == GPIO_NIBBLE_HIGH_BYTE_LOW)
		{
			GPIOA_ODR &=~(0x000000F0);
			GPIOA_ODR |=(Copy_u8NibbleVal<<4);

		}
		else if(Copy_NibblePosition == GPIO_NIBBLE_LOW_BYTE_HIGH)
		{
			GPIOA_ODR &=~(0x00000F00);
			GPIOA_ODR |=(Copy_u8NibbleVal<<8);

		}
		else if(Copy_NibblePosition == GPIO_NIBBLE_HIGH_BYTE_HIGH)
		{
			GPIOA_ODR &=~(0x0000F000);
			GPIOA_ODR |=(Copy_u8NibbleVal<<12);

		}
		else{}
		break;
	case GPIOB:
		if(Copy_NibblePosition == GPIO_NIBBLE_LOW_BYTE_LOW)
		{
			GPIOB_ODR &=~(0x0000000F);
			GPIOB_ODR |=(Copy_u8NibbleVal);
		}
		else if(Copy_NibblePosition == GPIO_NIBBLE_HIGH_BYTE_LOW)
		{
			GPIOB_ODR &=~(0x000000F0);
			GPIOB_ODR |=(Copy_u8NibbleVal<<4);

		}
		else if(Copy_NibblePosition == GPIO_NIBBLE_LOW_BYTE_HIGH)
		{
			GPIOB_ODR &=~(0x00000F00);
			GPIOB_ODR |=(Copy_u8NibbleVal<<8);

		}
		else if(Copy_NibblePosition == GPIO_NIBBLE_HIGH_BYTE_HIGH)
		{
			GPIOB_ODR &=~(0x0000F000);
			GPIOB_ODR |=(Copy_u8NibbleVal<<12);

		}
		else{}
		break;
	case GPIOC:
		if(Copy_NibblePosition == GPIO_NIBBLE_LOW_BYTE_LOW)
		{
			GPIOC_ODR &=~(0x0000000F);
			GPIOC_ODR |=(Copy_u8NibbleVal);
		}
		else if(Copy_NibblePosition == GPIO_NIBBLE_HIGH_BYTE_LOW)
		{
			GPIOC_ODR &=~(0x000000F0);
			GPIOC_ODR |=(Copy_u8NibbleVal<<4);

		}
		else if(Copy_NibblePosition == GPIO_NIBBLE_LOW_BYTE_HIGH)
		{
			GPIOC_ODR &=~(0x00000F00);
			GPIOC_ODR |=(Copy_u8NibbleVal<<8);

		}
		else if(Copy_NibblePosition == GPIO_NIBBLE_HIGH_BYTE_HIGH)
		{
			GPIOC_ODR &=~(0x0000F000);
			GPIOC_ODR |=(Copy_u8NibbleVal<<12);

		}
		else{}
		break;
	default :break;
	}
}


u8 MGPIO_voidGetByteVal(u8 Copy_u8PortId,u8 Copy_BytePosition)
{
	u8 result ;
	switch (Copy_u8PortId)
	{
	case GPIOA:
		if(Copy_BytePosition == GPIO_BYTE_POSITION_LOW)
		{
			result = (GPIOA_IDR & 0xFF);
		}
		else if (Copy_BytePosition == GPIO_BYTE_POSITION_HIGH)
		{
			result = ((GPIOA_IDR & (0xFF<<8)) >>8);
		}

		break;
	case GPIOB :
		if(Copy_BytePosition == GPIO_BYTE_POSITION_LOW)
		{
			result = (GPIOB_IDR & 0xFF);
		}
		else if (Copy_BytePosition == GPIO_BYTE_POSITION_HIGH)
		{
			result = ((GPIOB_IDR & (0xFF<<8)) >>8);
		}
		break;
	case GPIOC :
		if(Copy_BytePosition == GPIO_BYTE_POSITION_LOW)
		{
			result = (GPIOC_IDR & 0xFF);
		}
		else if (Copy_BytePosition == GPIO_BYTE_POSITION_HIGH)
		{
			result = ((GPIOC_IDR & (0xFF<<8)) >>8);
		}
		break;
	default :
		break;
	}
	return result ;
}

