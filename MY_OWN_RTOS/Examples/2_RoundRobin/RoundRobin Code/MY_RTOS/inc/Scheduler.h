/*
 * Scheduler.h
 *
 *  Created on: Jun 15, 2023
 *      Author: Ephraim
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include "CortexMX_OS_porting.h"
#include "MYRTOS_FIFO.h"



typedef enum {
	NoError,
	Ready_Queue_init_error,
	Task_exceeded_StackSize,
	MutexReachedToMaxNymberOfUsers,

}MYRTOS_errorID;

typedef struct {
	unsigned int Stack_Size ;		//Set By the User
	unsigned char priority ;		//Set By the User
	void (*p_TaskEntry)(void); 		//Set By the User -- pointer to Task C Function
	unsigned char AutoStart ;
	unsigned int _S_PSP_TASK ; 		//Not Entered by the user //Calculate By OS
	unsigned int _E_PSP_TASK ;		//Not Entered by the user //Calculate By OS
	unsigned int * Current_PSP ;	//Not Entered by the user // To can return to the same address in this task //Calculate By OS
	char TaskName[30];				//Set By the User
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

typedef struct {
	unsigned char 	*Ppayload ;		//Set by the User
	unsigned int 	PayloadSize ;	//Set by the User
	char			MutexName[30];	//Set by the User
	Task_ref*		CurrentTUser;  	//Not Set by the User
	Task_ref*		NextTUser;		//Not Set by the User
}Mutex_ref;

//APIs
MYRTOS_errorID MYRTOS_init();
MYRTOS_errorID MYRTOS_CreateTask(Task_ref *Tref);
MYRTOS_errorID MYRTOS_ActivateTask(Task_ref *Tref);
MYRTOS_errorID MYRTOS_TerminateTask(Task_ref *Tref);
void MYRTOS_STARTOS();

void MYRTOS_TaskWait(unsigned int NoTICKS,Task_ref *SelfTref );

MYRTOS_errorID MYRTOS_AcquireMutex(Mutex_ref* Mref , Task_ref* Tref);
void MYRTOS_ReleaseMutex(Mutex_ref* Mref);



#endif /* INC_SCHEDULER_H_ */
