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

#include "core_cm3.h"
#include "lcd.h"


uint8_t IRQ_Flag ,TASKA_flag , TASKB_flag;

#define TaskA_Stack_Size 100		//100 Byte
#define TaskB_Stack_Size 100		//100 Byte

extern int _estack;
//Main Stack
unsigned int _S_MSP =&_estack ;
unsigned int _E_MSP ;

//Process stack Task A
unsigned int _S_PSP_TA ;
unsigned int _E_PSP_TA ;

//Process stack Task B
unsigned int _S_PSP_TB ;
unsigned int _E_PSP_TB ;



#define OS_SET_PSP(add)							__asm volatile("mov r0,%0 \n\t msr PSP,r0" : :"r"(add))
#define OS_SWITCH_SP_to_PSP						__asm volatile("mrs r0,CONTROL \n\t mov r1,#0x02 \n\t orr r0,r1,r0 \n\t msr CONTROL ,r0")
#define OS_SWITCH_SP_to_MSP						__asm volatile("mrs r0,CONTROL \n\t mov r1,#0x05 \n\t and r0,r0,r1 \n\t msr CONTROL ,r0")
#define OS_Generate_Exception					__asm volatile("SVC #0x3")
#define SWITCH_CPU_AccessLevelPrivileged		__asm volatile("mrs r3, CONTROL  \n\t lsr r3 , r3 ,#0x1 \n\t lsl r3,r3,#0x1 \n\t msr CONTROL , r3")
#define SWITCH_CPU_AccessLevelUnprivileged		__asm volatile("mrs r3, CONTROL  \n\t orr r3 , r3 ,#0x1 \n\t msr CONTROL , r3")

int Control_Reg_Thread_Mode = 0 ;
int IPSR_Handler_Mode = 0;

enum CPUAccessLevel
{
	privileged ,
	unprivileged
};

void SWITCH_CPU_AccessLevel(enum CPUAccessLevel level)
{
	switch(level){
	case privileged :
		//Clear Bit 0 CONTROL register
		__asm("NOP");
		__asm("mrs r3, CONTROL  \n\t"
				"lsr r3,r3,#0x1 \n\t"
				"lsl r3,r3,#0x1 \n\t"
				"msr CONTROL , r3");
		__asm("NOP");
		break;

	case unprivileged:
		//Set Bit 0 CONTROL register
		__asm("NOP");
		__asm("mrs r3, CONTROL 		\n\t"
				"orr r3 , r3 ,#0x1  \n\t"
				"msr CONTROL , r3");
		__asm("NOP");
		break;

	}
}


void NMI_Handler (void)
{

}

void HardFault_Handler (void)
{

}

void BusFault_Handler (void)
{

}

void EXTI9_CALLBACK(void)
{
	if(IRQ_Flag == 0 )
	{
		TASKA_flag=1;
		IRQ_Flag = 1;
	}else if (IRQ_Flag == 1)
	{
		TASKB_flag=1;
		IRQ_Flag = 0;

	}

}

//void SVC_Handler(void)
//{
//	SWITCH_CPU_AccessLevelPrivileged;
//}
int TaskA(int a, int b , int c)
{

	return a+b+c;
}

int TaskB(int a, int b , int c ,int d)
{

	return a+b+c+d;
}

void MainOs()
{
	//Main Stack
	_E_MSP =_S_MSP -512 ;

	//Task A
	_S_PSP_TA = (_E_MSP - 8);
	_E_PSP_TA = (_S_PSP_TA -TaskA_Stack_Size);

	//Task B
	_S_PSP_TB =(_E_PSP_TA - 8 );
	_E_PSP_TB =(_S_PSP_TB - TaskB_Stack_Size);

	while (1)
	{
		__asm("NOP");
		if(TASKA_flag)
		{
			//Set PSP Register = _S_PSP_TA
			OS_SET_PSP(_S_PSP_TA);
			//SP->PSP
			OS_SWITCH_SP_to_PSP;
			//Switch from privileged --> unprivileged
			SWITCH_CPU_AccessLevelUnprivileged;
			TASKA_flag = TaskA(1,2,3);

			//Switch from unprivileged --> privileged
			OS_Generate_Exception;
			//SP->MSP
			OS_SWITCH_SP_to_MSP;

			TASKA_flag = 0 ;

		}else if(TASKB_flag)
		{
			//Set PSP Register = _S_PSP_TB
			OS_SET_PSP(_S_PSP_TB);
			//SP->PSP
			OS_SWITCH_SP_to_PSP;
			//Switch from privileged --> unprivileged
			SWITCH_CPU_AccessLevelUnprivileged;

			TASKB_flag = TaskB(1,2,3,4);

			//Switch from unprivileged --> privileged
			OS_Generate_Exception;
			//SP->MSP
			OS_SWITCH_SP_to_MSP;

			TASKB_flag = 0 ;
		}
	}
}

void PendSV_Handler(void)
{

}



void OS_SVC_services(int *StackFramePointer)
{
	//OS_SVC_Set Stack -> r0 -> argument0 = StackFramePointer
	//OS_SVC_Set Stack -> r0,r1,r2,r3,r12,LR,PC,xPSR

	unsigned char SVC_number ;
	unsigned int val1 , val2 ;
	val1 = StackFramePointer[0];
	val2 = StackFramePointer[1];

	SVC_number= *((unsigned char *)(((unsigned char *)StackFramePointer[6])-2));

	switch (SVC_number)
	{
	case 1 ://ADD
		StackFramePointer[0]=val1 + val2;
		break;
	case 2 ://Sub
		StackFramePointer[0]=val1 - val2;
		break;
	case 3://MULT
		StackFramePointer[0]=val1 * val2;
		break;
	case 4:	//OS PendSV
		SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
		break;


	}
}
__attribute ((naked)) void SVC_Handler(void)
{
	__asm("tst lr, #0x04 	\n\t"
		  "ITE EQ			\n\t"
		  "mrseq r0,MSP		\n\t"
		  "mrsne r0,PSP		\n\t"
		  "B OS_SVC_services ");
}

int OS_SVC_Set(int a , int b , int SVC_ID )
{
	int return_Val ;
	switch (SVC_ID)
	{
	case 1:	//ADD
		__asm("svc #0x01");
		break;
	case 2:	//SUB
		__asm("svc #0x02");
		break;
	case 3:	//MULT
		__asm("svc #0x03");
		break;
	case 4:	//OS PendSV
		__asm("svc #0x04");
		break;
	}
	//r0 will have the return Value
	__asm("mov %0 ,r0":"=r"(return_Val));
	return return_Val;
}


int main(void)
{

//	//Enable GPIOA and GPIOB and AFIO
//	RCC_GPIOB_CLK_EN();
//	RCC_AFIO_CLK_EN();
//
//
//
//	//Set EXTI Configuration
//	EXTI_PinConfig_t EXTIConfig ;
//	EXTIConfig.EXTI_PIN=EXTI9PB9;
//	EXTIConfig.Trigger_Case=EXTI_Trigger_RISING;
//	EXTIConfig.P_IRQ_CallBack=EXTI9_CALLBACK;
//	EXTIConfig.IRQ_EN=EXTI_IRQ_Enable;
//	MCAL_EXTI_GPIO_Init(&EXTIConfig);
//
//	//Enable NVIC
//	NVIC_IRQ23_EXTI5_9_Enable;
//
//	MainOs();
//	SWITCH_CPU_AccessLevel(unprivileged);


	OS_SVC_Set(3,3,1);
	OS_SVC_Set(3,3,2);
	OS_SVC_Set(3,3,3);
	OS_SVC_Set(3,3,4);

	IRQ_Flag=1;

	while (1)
	{
		if(IRQ_Flag)
		{
			IRQ_Flag=0;
		}
		else{/* Misra */}
	}
}







