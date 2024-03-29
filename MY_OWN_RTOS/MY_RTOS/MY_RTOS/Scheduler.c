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


typedef enum {
	SVC_ActivateTask,
	SVC_TerminateTask,
	SVC_TaskWaitingTime,
	SVC_AquireMutex,
	SVC_ReleaseMutex
}SVC_ID;



FIFO_Buf_t Ready_QUEUE ;
Task_ref* Ready_QUEUE_FIFO[10];
Task_ref MYRTOS_idleTask ;







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

unsigned char IdleTaskLed ;
void MYRTOS_IdleTask ()
{
	while(1)
	{
		IdleTaskLed ^=1;
		__asm("wfe");//Wait for Event
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
	if(FIFO_init(&Ready_QUEUE, Ready_QUEUE_FIFO, 10)!=FIFO_no_error)
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

	//Update Scheduler Table
	OS_Control.OSTasks[OS_Control.NoOfActiveTasks]=Tref;
	OS_Control.NoOfActiveTasks++;

	//Task State Update -> Suspend
	Tref->TaskState=Suspend;

	return error ;
}

//Handler
void bubbleSort()
{
	unsigned int i , j , n;
	Task_ref* temp ;
	n = OS_Control.NoOfActiveTasks;

	for (i =0 ;i< (n-1); i++)
	{
		//Last i elements are already in place
		for (j =0 ; j< (n-i-1 ) ; j++)
		{
			if (OS_Control.OSTasks[j]->priority > OS_Control.OSTasks[j+1]->priority)
			{
				temp =OS_Control.OSTasks[j];
				OS_Control.OSTasks[j]=OS_Control.OSTasks[j+1];
				OS_Control.OSTasks[j+1]=temp;
			}
		}
	}

}


//Handler
void MYRTOS_Update_Schedule_tables()
{
	Task_ref* temp =NULL ;
	Task_ref* Ptask;
	Task_ref* PnextTask;
	int i =0;
	//1-Bubble Sort Scheduler Table OS_Control->OSTASKS[100] (priority high than low)
	bubbleSort();
	//2-free Ready Queue
	while(FIFO_dequeue(&Ready_QUEUE, &temp)!= FIFO_empty);
	//3-update ready Queue
	while(i< OS_Control.NoOfActiveTasks)
	{
		Ptask = OS_Control.OSTasks[i];
		PnextTask = OS_Control.OSTasks[i+1];

		if(Ptask->TaskState != Suspend)
		{
			//in case we reached to the end of available OSTASKS
			//Here Bug "Logical Error"
			if(PnextTask->TaskState == Suspend )
			{
				FIFO_enqueue(&Ready_QUEUE, Ptask);
				Ptask->TaskState =ready;
				break;
			}
			// if the Ptask priority > PnextTask priority then (lowest number is meaning higher priority)
			if(Ptask->priority < PnextTask->priority)
			{
				FIFO_enqueue(&Ready_QUEUE, Ptask);
				Ptask->TaskState =ready;
				break;
			}
			else if (Ptask->priority == PnextTask->priority)
			{
				//if the Ptask priority == PnextTask then
				//	push Ptask to ready state
				//and make the ptask = PnextTask and
				FIFO_enqueue(&Ready_QUEUE, Ptask);
				Ptask->TaskState =ready;
			}
			else if (Ptask->priority > PnextTask->priority)
			{
				//not allowed to happen as we already reordered it bu bubble sort
			}

		}

		i++;
	}
}
//Handler Mode
void Decide_whatNext()
{
	// if Ready Queue is empty && OS_Control.currentTask->TaskState !=suspend
	// The Condition Here Logical Bug
	if(Ready_QUEUE.count == 0 && OS_Control.CurrentTask->TaskState != Suspend)
	{
		OS_Control.CurrentTask->TaskState=Running;
		//add the current task again (round robin)
		FIFO_enqueue(&Ready_QUEUE, OS_Control.CurrentTask);
		//To Switch Context
		OS_Control.NextTask=OS_Control.CurrentTask;
	}else
	{
		FIFO_dequeue(&Ready_QUEUE, &OS_Control.NextTask);//Put the first element in the fifo into NextTask to switch to it in PendSv Handler
		OS_Control.NextTask->TaskState=Running;

		//update Ready queue (to keep round robin algorithm happen)
		//Logic error current task will be there twice
		if((OS_Control.CurrentTask->priority == OS_Control.NextTask->priority)&&(OS_Control.CurrentTask->TaskState!= Suspend) )
		{
			FIFO_enqueue(&Ready_QUEUE, OS_Control.CurrentTask);
			OS_Control.CurrentTask->TaskState=ready;
		}
	}

}

__attribute ((naked))void PendSV_Handler()
{
	//====================================
	//Save the Context of the Current Task
	//====================================
	//Get the Current Task "Current PSP from CPU register as CPU push xpsr to r0"
	//I Think this line haven't affect
	OS_GET_PSP(OS_Control.CurrentTask->Current_PSP);

	//using this Current_PSP(Pointer) to store (R4 to R11)
	OS_Control.CurrentTask->Current_PSP--;
	__asm volatile("mov %0 ,r4":"=r"(*(OS_Control.CurrentTask->Current_PSP)) );
	OS_Control.CurrentTask->Current_PSP--;
	__asm volatile("mov %0 ,r5":"=r"(*(OS_Control.CurrentTask->Current_PSP)) );
	OS_Control.CurrentTask->Current_PSP--;
	__asm volatile("mov %0 ,r6":"=r"(*(OS_Control.CurrentTask->Current_PSP)) );
	OS_Control.CurrentTask->Current_PSP--;
	__asm volatile("mov %0 ,r7":"=r"(*(OS_Control.CurrentTask->Current_PSP)) );
	OS_Control.CurrentTask->Current_PSP--;
	__asm volatile("mov %0 ,r8":"=r"(*(OS_Control.CurrentTask->Current_PSP)) );
	OS_Control.CurrentTask->Current_PSP--;
	__asm volatile("mov %0 ,r9":"=r"(*(OS_Control.CurrentTask->Current_PSP)) );
	OS_Control.CurrentTask->Current_PSP--;
	__asm volatile("mov %0 ,r10":"=r"(*(OS_Control.CurrentTask->Current_PSP)) );
	OS_Control.CurrentTask->Current_PSP--;
	__asm volatile("mov %0 ,r11":"=r"(*(OS_Control.CurrentTask->Current_PSP)) );

	//save the Current Value of PSP
	//Already saved in Current_PSP

	//====================================
	//Restore the Context of the Next Task
	//====================================
	if(OS_Control.NextTask != NULL)
	{
		OS_Control.CurrentTask=OS_Control.NextTask;
		OS_Control.NextTask=NULL;
	}
	__asm volatile("mov r11 ,%0" : :"r"(*(OS_Control.CurrentTask->Current_PSP)) );
	OS_Control.CurrentTask->Current_PSP++;
	__asm volatile("mov r10 ,%0" : :"r"(*(OS_Control.CurrentTask->Current_PSP)) );
	OS_Control.CurrentTask->Current_PSP++;
	__asm volatile("mov r9  ,%0" : :"r"(*(OS_Control.CurrentTask->Current_PSP)) );
	OS_Control.CurrentTask->Current_PSP++;
	__asm volatile("mov r8  ,%0" : :"r"(*(OS_Control.CurrentTask->Current_PSP)) );
	OS_Control.CurrentTask->Current_PSP++;
	__asm volatile("mov r7  ,%0" : :"r"(*(OS_Control.CurrentTask->Current_PSP)) );
	OS_Control.CurrentTask->Current_PSP++;
	__asm volatile("mov r6  ,%0" : :"r"(*(OS_Control.CurrentTask->Current_PSP)) );
	OS_Control.CurrentTask->Current_PSP++;
	__asm volatile("mov r5  ,%0" : :"r"(*(OS_Control.CurrentTask->Current_PSP)) );
	OS_Control.CurrentTask->Current_PSP++;
	__asm volatile("mov r4  ,%0" : :"r"(*(OS_Control.CurrentTask->Current_PSP)) );
	OS_Control.CurrentTask->Current_PSP++;

	//update PSP and exit
	OS_SET_PSP(OS_Control.CurrentTask->Current_PSP);

	__asm("BX LR");
}

//Handler Mode
void OS_SVC (int* stackFrame)
{
	//OS_SVC_Set Stack -> r0 -> argument0 = StackFramePointer
	//OS_SVC_Set Stack -> r0,r1,r2,r3,r12,LR,PC,xPSR
	unsigned char SVC_number ;
	SVC_number= *((unsigned char *)(((unsigned char *)stackFrame[6])-2));
	switch(SVC_number)
	{
	case SVC_ActivateTask:
	case SVC_TerminateTask:
		//Update scheduler Table , Ready Queue
		MYRTOS_Update_Schedule_tables();
		//if OS is in Running State
		if(OS_Control.OSmodeID == OsRunning)
		{
			if(strcmp(OS_Control.CurrentTask->TaskName,"idleTask") !=0)
			{
				//Decide what Next
				Decide_whatNext();
				//Trigger OS_pendSV (Switch Context/Restore)
				trigger_OS_PendSV();
			}
		}


		break;
	case SVC_TaskWaitingTime:
		//Update scheduler Table , Ready Queue
		MYRTOS_Update_Schedule_tables();

		break;
	}


}

//Thread Mode
void MYRTOS_OS_SVC_SET(SVC_ID ID)
{
	switch(ID)
	{
	case SVC_ActivateTask:
		__asm("svc #0x00");
		break;
	case SVC_TerminateTask:
		__asm("svc #0x01");
		break;
	case SVC_TaskWaitingTime:
		__asm("svc #0x02");
		break;
	case SVC_AquireMutex:		//Assignment Task
		__asm("svc #0x03");
		break;
	case SVC_ReleaseMutex:		//Assignment Task
		__asm("svc #0x04");
		break;
	}
}
MYRTOS_errorID MYRTOS_ActivateTask(Task_ref *Tref)
{
	Tref->TaskState=Waiting;
	MYRTOS_OS_SVC_SET(SVC_ActivateTask);

}
MYRTOS_errorID MYRTOS_TerminateTask(Task_ref *Tref)
{
	Tref->TaskState=Suspend;
	MYRTOS_OS_SVC_SET(SVC_TerminateTask);
}

void MYRTOS_TaskWait(unsigned int NoTICKS,Task_ref *SelfTref )
{
	SelfTref->TimingWaiting.Blocking=Enable;
	SelfTref->TimingWaiting.Ticks_Count =NoTICKS;
	//Task Should be Blocked
	SelfTref->TaskState=Suspend;
	//To be suspended immediately
	MYRTOS_OS_SVC_SET(SVC_TerminateTask);

}

void MYRTOS_STARTOS()
{
	OS_Control.OSmodeID=OsRunning;
	//Set Default "Current Task idle Task"
	OS_Control.CurrentTask=&MYRTOS_idleTask;
	//Activate IDLE Task
	MYRTOS_ActivateTask(&MYRTOS_idleTask);
	//Start Ticker
	Start_Tiker(); // 1ms

	OS_SET_PSP(OS_Control.CurrentTask->Current_PSP);
	//Switch Thread Mode Sp from MSP to PSP
	OS_SWITCH_SP_to_PSP;
	OS_SWITCH_to_unprivileged;

	MYRTOS_idleTask.p_TaskEntry();

}


void MYRTOS_Update_TasksWaitingTime()
{
	for (int i =0 ; i <OS_Control.NoOfActiveTasks ;i++)
	{
		//it is blocked until meet the time line
		if(OS_Control.OSTasks[i]->TaskState == Suspend)
		{
			if(OS_Control.OSTasks[i]->TimingWaiting.Blocking ==Enable)
			{
				OS_Control.OSTasks[i]->TimingWaiting.Ticks_Count--;
				if(OS_Control.OSTasks[i]->TimingWaiting.Ticks_Count ==0)
				{
					OS_Control.OSTasks[i]->TimingWaiting.Blocking =Disable;
					OS_Control.OSTasks[i]->TaskState=Waiting;
					MYRTOS_OS_SVC_SET(SVC_TaskWaitingTime);
				}
			}
		}
	}
}





