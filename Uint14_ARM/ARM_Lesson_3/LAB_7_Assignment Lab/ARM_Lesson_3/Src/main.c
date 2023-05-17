/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */


#include "stm32f103x6.h"
#include "STM32_F103C6_GPIO_Driver.h"
#include "STM32_F103C6_EXTI_Driver.h"


#include "lcd.h"
uint8_t IRQ_Flag;

int Control_Reg_Thread_Mode = 0 ;
int IPSR_Handler_Mode = 0;

void EXTI9_CALLBACK(void)
{
	IRQ_Flag=1;

	__asm("NOP \n\t NOP \n\t NOP \n\t");

	__asm("MRS %[out0], IPSR"
		  :[out0] "=r" (IPSR_Handler_Mode) );

	__asm("NOP \n\t NOP \n\t NOP \n\t");
}

int main(void)
{

	//Enable GPIOA and GPIOB and AFIO
	RCC_GPIOB_CLK_EN();
	RCC_AFIO_CLK_EN();

	//Set EXTI Configuration
	EXTI_PinConfig_t EXTIConfig ;
	EXTIConfig.EXTI_PIN=EXTI9PB9;
	EXTIConfig.Trigger_Case=EXTI_Trigger_RISING;
	EXTIConfig.P_IRQ_CallBack=EXTI9_CALLBACK;
	EXTIConfig.IRQ_EN=EXTI_IRQ_Enable;
	MCAL_EXTI_GPIO_Init(&EXTIConfig);

	//Enable NVIC
	NVIC_IRQ23_EXTI5_9_Enable;


	IRQ_Flag=1;

	__asm("NOP \n\t NOP \n\t NOP \n\t");

	__asm("MRS %[out0], control"
		  :[out0] "=r" (Control_Reg_Thread_Mode) );

	__asm("NOP \n\t NOP \n\t NOP \n\t");

	while (1)
	{
		if(IRQ_Flag)
		{
			IRQ_Flag=0;
		}
		else{/* Misra */}
	}
}











//__asm("NOP \n\t NOP \n\t NOP \n\t");
//
//	//mov R0 , VAL1
//
//	__asm("mov r0,%0"
//		  :					// First  : Output Parameter
//		  :"r" (VAL1) ); 	// Second :	Input Parameters
//
//	__asm("NOP \n\t NOP \n\t NOP \n\t");






