/*
 * STK_program.c
 *
 *  Created on: Mar 5, 2023
 *      Author: Ephraim
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "STK_interface.h"
#include "STK_private.h"
#include "STK_config.h"

void (* STKCallBack )(void);

#define INTERVAL_MODE_SINGLE		0
#define INTERVAL_MODE_PERIODIC		1

u8 Gobal_u8IntervalMode =INTERVAL_MODE_SINGLE;

void MSTK_voidInit(void)
{
	//Disable SysTick
	CLR_BIT(STK->CTRL , 0);
	//Disable SysTick Interrupt
	CLR_BIT(STK->CTRL , 1);

	//Apply Clock Choice from Configuration File
	if(STK_CLK_SOURCE==STK_AHB)
	{
		SET_BIT(STK->CTRL,2);
	}
	else if(STK_CLK_SOURCE==STK_AHB_OVER_8)
	{
		CLR_BIT(STK->CTRL,2);
	}
	else{}


}


void MSTK_voidSetBusyWait(u32 Copy_u32Ticks)
{
	//Enable SysTick
	SET_BIT(STK->CTRL , 0);
	//Disable SysTick Interrupt
	CLR_BIT(STK->CTRL , 1);
	CLR_BIT(STK->CTRL , 16);
	if(Copy_u32Ticks <= 0x00FFFFFF)
	{
		STK->LOAD = Copy_u32Ticks;
		//Loop Until Count FLAG = 1
		while(GET_BIT(STK->CTRL,16)==0);
	}
	else{}
}


void MSTK_voidResetTimerVal(void)
{
	STK->VAL = 0;

}
void MSTK_voidStopTimer				(void)
{
	STK->LOAD = 0 ;
	STK->VAL =  0 ;

}

void MSTK_voidSetIntervalSingle(u32 Copy_u32Ticks ,void (*Copy_ptr) (void))
{
	CLR_BIT(STK->CTRL , 0)  ;
	STK->VAL = 0;


	if(Copy_u32Ticks <= 0x00FFFFFF)
	{
		STK->LOAD=Copy_u32Ticks;
	}
	//Save CallBack
	STKCallBack=Copy_ptr;

	//Enable SysTick Interrupt
	SET_BIT(STK->CTRL , 1);

	//Enable SysTick
	SET_BIT(STK->CTRL , 0);

	/*Set Mode to Be Single*/
	Gobal_u8IntervalMode = INTERVAL_MODE_SINGLE;



}



void MSTK_voidSetIntervalPeriodic	(u32 Copy_u32Ticks , void (*Copy_ptr) (void))
{
	Gobal_u8IntervalMode = INTERVAL_MODE_PERIODIC;
	//Enable SysTick
	SET_BIT(STK->CTRL , 0);
	//Enable SysTick Interrupt
	SET_BIT(STK->CTRL , 1);

	STKCallBack=Copy_ptr;

	if(Copy_u32Ticks <= 0x00FFFFFF)
	{
		STK->LOAD=Copy_u32Ticks;
	}

}

u32 MSTK_u32GetElapsedTime			(void)
{
	u32 Local_u32ElapsedTime;

	Local_u32ElapsedTime = (STK->LOAD-STK->VAL);

	return Local_u32ElapsedTime;
}
u32 MSTK_u32GetRemainingTime		(void)
{
	u32 Local_u32RemainingTime;

	Local_u32RemainingTime=STK->VAL;

	return Local_u32RemainingTime;

}








void SysTick_Handler(void)
{


	STKCallBack();

	if(Gobal_u8IntervalMode==INTERVAL_MODE_SINGLE)
	{
		STK->VAL = 0;
		STK->CTRL = 0 ;


	}



}



