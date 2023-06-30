/*
 * CortexMX_OS_porting.c
 *
 *  Created on: Jun 15, 2023
 *      Author: Ephraim
 */


#include "CortexMX_OS_porting.h"


unsigned char  SysTickLED;


 void HardFault_Handler (void)
 {
	 while(1);
 }
 void MemManage_Handler (void)
 {
	 while(1);
 }
 void BusFault_Handler (void)
 {
	 while(1);
 }
 void UsageFault_Handler (void)
 {
	 while(1);
 }

 __attribute ((naked)) void SVC_Handler(void)
 {
 	__asm("tst lr, #0x04 	\n\t"
 		  "ITE EQ			\n\t"
 		  "mrseq r0,MSP		\n\t"
 		  "mrsne r0,PSP		\n\t"
 		  "B OS_SVC ");
 }

void HW_init()
{
	//Initialize CLock Tree (RCC -> Systick Timer & CPU ) 8MHz
	//init HW
	//Clock tree
	//RCC Default Values makes CPU Clock & SysTick Timer clock = 8MHz



	// 8MHz
	// 1 count -> 0.125 us
	// X count -> 1 ms
	// X = 8000 Count

	//decrease PendSV interrupt priority to be smaller than or equal SYStick Timer
	//SYSTICK have a priority 14
	__NVIC_SetPriority(PendSV_IRQn, 15);

}


void trigger_OS_PendSV()
{
	SCB->ICSR |=SCB_ICSR_PENDSVSET_Msk;
}


void Start_Tiker()
{
	SysTick_Config(8000);
}


void SysTick_Handler(void)
{
	SysTickLED ^=1;
	MYRTOS_Update_TasksWaitingTime();
	//determine pCurrrent and pNext
	Decide_whatNext();
	//Switch Context
	trigger_OS_PendSV();
}










