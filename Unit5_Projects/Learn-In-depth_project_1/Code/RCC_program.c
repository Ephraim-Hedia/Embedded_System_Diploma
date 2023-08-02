/********************************************************************************/
/* Author 			: Guirguis Hedia 											*/
/* Date 			: 20 Feb 2023												*/
/* Version 			: V01														*/
/********************************************************************************/


#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "RCC_private.h"
#include "RCC_config.h"

//Private Function
void RCC_voidEnableCLKs(void)
{
	//Enable Internal CLK
#ifdef RCC_HSI_ENABLE
	SET_BIT(RCC_CR,0);
#else
	CLR_BIT(RCC_CR,0);
#endif

	//Enable External CLK
#ifdef RCC_HSE_ENABLE
	SET_BIT(RCC_CR,16);
#else
	CLR_BIT(RCC_CR,16);
#endif

	//Enable PLL Circuit
#ifdef	RCC_PLL_ENABLE
	SET_BIT(RCC_CR,24);
#else
	CLR_BIT(RCC_CR,24);
#endif
}


//Private Function
void RCC_voidSetSystemClk(void)
{
#if (SYSTEM_CLK_SOURCE==RCC_HSI_CLK)
	CLR_BIT(RCC_CFGR,0);CLR_BIT(RCC_CFGR,1);

#elif(SYSTEM_CLK_SOURCE==RCC_HSE_CLK)
	SET_BIT(RCC_CFGR,0);CLR_BIT(RCC_CFGR,1);

#elif(SYSTEM_CLK_SOURCE==RCC_PLL_CLK)
	CLR_BIT(RCC_CFGR,0);SET_BIT(RCC_CFGR,1);

#endif
}



void RCC_voidSetMCOSource(void)
{

#if (RCC_MCO_SOURCE==RCC_MCO_NO_CLK)
	CLR_BIT(RCC_CFGR,26);CLR_BIT(RCC_CFGR,25);CLR_BIT(RCC_CFGR,24);

#elif (RCC_MCO_SOURCE==RCC_MCO_SYSCLK)
	SET_BIT(RCC_CFGR,26);CLR_BIT(RCC_CFGR,25);CLR_BIT(RCC_CFGR,24);

#elif (RCC_MCO_SOURCE==RCC_MCO_HSI)
	SET_BIT(RCC_CFGR,26);CLR_BIT(RCC_CFGR,25);SET_BIT(RCC_CFGR,24);

#elif(RCC_MCO_SOURCE==RCC_MCO_HSE)
	SET_BIT(RCC_CFGR,26);SET_BIT(RCC_CFGR,25);CLR_BIT(RCC_CFGR,24);

#elif(RCC_MCO_SOURCE==RCC_MCO_PLLCLK)
	SET_BIT(RCC_CFGR,26);SET_BIT(RCC_CFGR,25);SET_BIT(RCC_CFGR,24);

#endif

}


void RCC_voidInitSystemClk(void)
{

	//Enable Clks Internal Circuit
	//NOTE:Thats not mean The The clk will be the system clk
	RCC_voidEnableCLKs();

	//Choose System Clk Source which will connect with the processor
	RCC_voidSetSystemClk();

	//Choose MCO Source
	RCC_voidSetMCOSource();

	//Trimming
#if(SYSTEM_CLK_SOURCE==RCC_HSI_CLK)
	RCC_CR |= ((unsigned char)((RCC_HSI_Trimming&0b00011111) <<3));
#endif

	//	return RCC_OK;
}


void RCC_u8EnableClock(u8 Copy_u8BusId,u8 Copy_u8PerId)
{
	if(Copy_u8PerId <=31)
	{
		switch(Copy_u8BusId)
		{
		case RCC_AHB  :	SET_BIT(RCC_AHBENR ,Copy_u8PerId);	break;
		case RCC_APB1 : SET_BIT(RCC_APB1ENR,Copy_u8PerId);	break;
		case RCC_APB2 : SET_BIT(RCC_APB2ENR,Copy_u8PerId);	break;


		}

	}

	else
	{
		//Report Error
	}
}

void RCC_u8DisableClock(u8 Copy_u8BusId,u8 Copy_u8PerId)
{
	if(Copy_u8PerId <=31)
	{
		switch(Copy_u8BusId)
		{
		case RCC_AHB  :	CLR_BIT(RCC_AHBENR ,Copy_u8PerId);	break;
		case RCC_APB1 : CLR_BIT(RCC_APB1ENR,Copy_u8PerId);	break;
		case RCC_APB2 : CLR_BIT(RCC_APB2ENR,Copy_u8PerId);	break;


		}

	}

	else
	{
		//Report Error
	}
}
















