/*
 * Scheduler.c
 *
 *  Created on: Jun 15, 2023
 *      Author: Ephraim
 */


#include "Scheduler.h"
#include "MYRTOS_FIFO.h"


struct {
	Task_ref* OSTasks[100]; 	//Scheduler Table
	unsigned int _S_MSP_Task ;
	unsigned int _E_MSP_Task ;
	unsigned int PSP_Task_Locator ; // To be can create a new task . like linker locator in linkerScript file
	unsigned int NoOfActiveTasks ;
	Task_ref* CurrentTask;
	Task_ref* NextTask;
	enum{
		OSsuspend,//Not the Task , This for OS
		OsRunning//Not the Task , This for OS
	}OSmodeID;
}OS_Control ;

FIFO_Buf_t Ready_QUEUE ;
Task_ref* Ready_QUEUE_FIFO[100];
Task_ref MYRTOS_idleTask ;



 void OS_SVC_services(int *StackFramePointer)
 {
 	//OS_SVC_Set Stack -> r0 -> argument0 = StackFramePointer
 	//OS_SVC_Set Stack -> r0,r1,r2,r3,r12,LR,PC,xPSR

 	unsigned char SVC_number ;

 	SVC_number= *((unsigned char *)(((unsigned char *)StackFramePointer[6])-2));

 	switch (SVC_number)
 	{
 	case 1 ://Activate Task

 		break;
 	case 2 ://Terminate Task

 		break;
 	case 3://MULT

 		break;
 	case 4:	//OS PendSV

 		break;


 	}
 }


 void PendSV_Handler()
 {

 }


 void OS_SVC_Set(int SVC_ID )
 {

 	switch (SVC_ID)
 	{
 	case 1:	//Activate Task
 		__asm("svc #0x00");
 		break;
 	case 2:	//Terminate Task
 		__asm("svc #0x01");
 		break;
 	case 3:	//OS MUL
 		__asm("svc #0x02");
 		break;
 	case 4:	//OS PendSV
 		__asm("svc #0x03");
 		break;
 	}

 }

 MYRTOS_errorID MYRTOS_Create_MainStack()
 {
	 OS_Control._S_MSP_Task=(unsigned int)&_estack;
	 OS_Control._E_MSP_Task=OS_Control._S_MSP_Task - MainStackSize ;

	 //if (_E_MSP_Task < &_eheap) Error : exceeded the available stack size
	 if(OS_Control._E_MSP_Task < (unsigned int )(&_eheap))
	 {
		 return Task_exceeded_StackSize;
	 }


	 //Aligned 8 Byte spaces between Main Task and PSP Tasks
	 OS_Control.PSP_Task_Locator=(OS_Control._E_MSP_Task - 8);

	 return NoError;


 }

 void MYRTOS_IdleTask ()
 {
 	while(1)
 	{
 		__asm("NOP");
 	}
 }

 MYRTOS_errorID MYRTOS_init()
 {
	 MYRTOS_errorID error =NoError;

	 //Update OS Mode (OSsuspend)
	 OS_Control.OSmodeID = OSsuspend;

	 //Specify the main Stack for OS
	 error +=MYRTOS_Create_MainStack();
	 //Create OS Ready Queue
	 if(FIFO_init(&Ready_QUEUE, Ready_QUEUE_FIFO, 100)!=FIFO_no_error)
	 {
		 error +=Ready_Queue_init_error;
	 }

	 //Configure IDLE TASK
	 strcpy(MYRTOS_idleTask.TaskName,"idleTask");
	 MYRTOS_idleTask.priority =255;
	 MYRTOS_idleTask.p_TaskEntry=MYRTOS_IdleTask;
	 MYRTOS_idleTask.Stack_Size=300;

	 error += MYRTOS_CreateTask(&MYRTOS_idleTask);


	 return error ;
 }




void MyRTOS_Create_TaskStack(Task_ref *Tref)
{
	/*Task Frame
	 * ============
	 * xPSR
	 * PC (Next Task Instruction which should be Run )
	 * LR (return register which is saved in CPU while Task1 running before TaskSwitching)
	 * r12
	 * r3
	 * r2
	 * r1
	 * r0

	 * ========
	 * r4 ,r5 ,r6 ,r7 ,r8 ,r9,r10,r11 (Saved /Restore) Manual
	 */
	Tref->Current_PSP =Tref->_S_PSP_TASK;

	Tref->Current_PSP--;
	*(Tref->Current_PSP)=0x01000000; 	//Dummy xPSR should T=1 in bit 24 to avoid BusFault ;

	Tref->Current_PSP--;
	*(Tref->Current_PSP) = (unsigned int)Tref->p_TaskEntry; //PC

	Tref->Current_PSP--;	//LR =0xFFFFFFFD (EXC_RETURN) return to thread with PSP
	*(Tref->Current_PSP) = 0xFFFFFFFD;

	for (int j=0 ; j<13 ; j++)
	{
		Tref->Current_PSP--;
		*(Tref->Current_PSP) =0;
	}




}

MYRTOS_errorID MYRTOS_CreateTask(Task_ref *Tref)
{
	MYRTOS_errorID error =NoError;

	//Create its Own PSP stack
	//Check Task Stack size exceeded the PSP stack
	Tref->_S_PSP_TASK = OS_Control.PSP_Task_Locator;
	Tref->_E_PSP_TASK = Tref->_S_PSP_TASK - Tref->Stack_Size;

	//-						-
	//-	_S_PSP_Task			-
	//-	Task Stack 			-
	//-	_E_PSP_Task			-
	//-						-
	//-						-
	//-	_eheap				-
	//-						-

	if(Tref->_E_PSP_TASK < (unsigned int )(&_eheap))
	{
		return Task_exceeded_StackSize;
	}

	//Aligned 8 Bytes spaces between Task PSP and other
	OS_Control.PSP_Task_Locator = (Tref->_E_PSP_TASK -8 );

	//Initialize PSP Task Stack
	MyRTOS_Create_TaskStack(Tref);

	//Task State Update -> Suspend
	Tref->TaskState=Suspend;

	return error ;
}















