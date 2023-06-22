/*
 * Scheduler.h
 *
 *  Created on: Jun 15, 2023
 *      Author: Ephraim
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include "CortexMX_OS_porting.h"


typedef enum {
	NoError,
	Ready_Queue_init_error,
	Task_exceeded_StackSize
}MYRTOS_errorID;

typedef struct {
	unsigned int Stack_Size ;
	unsigned char priority ;
	void (*p_TaskEntry)(void); 		//pointer to Task C Function
	unsigned char AutoStart ;
	unsigned int _S_PSP_TASK ; 		//Not Entered by the user
	unsigned int _E_PSP_TASK ;		//Not Entered by the user
	unsigned int * Current_PSP ;	//Not Entered by the user // To can return to the same address in this task
	char TaskName[30];
	enum{
		Suspend,
		Running,
		Waiting,
		ready
	}TaskState	;	//Not Entered by the user
	struct{
		enum{
			Enable,
			Disable
		}Blocking;
		unsigned int Ticks_Count;
	}TimingWaiting;

}Task_ref;



//APIs
MYRTOS_errorID MYRTOS_init();
MYRTOS_errorID MYRTOS_CreateTask(Task_ref *Tref);
MYRTOS_errorID MYRTOS_ActivateTask(Task_ref *Tref);
MYRTOS_errorID MYRTOS_TerminateTask(Task_ref *Tref);
void MYRTOS_STARTOS();

#endif /* INC_SCHEDULER_H_ */
