/*
 * CortexMX_OS_porting.c
 *
 *  Created on: Jun 15, 2023
 *      Author: Ephraim
 */


#include "CortexMX_OS_porting.h"

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
 		  "B OS_SVC_services ");
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

}
