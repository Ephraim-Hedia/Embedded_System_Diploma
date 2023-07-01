# MY OWN RTOS


First of all The MRTOS is implemented for educational and learning purposes so it may exist some faults I didn't handle so u can upload them in the issue section or fork the project and try to add your modification.
## Getting help
Feel Free to contact me, just message me at <br/>
Linkedin at https://www.linkedin.com/in/guirguis-hedia-501446207/<br/>
Facebook at https://www.facebook.com/afraem.hedia<br/>
with your question.<br/>

# How to Use This RTOS
## First Step 
Use HW_init() in main Function to Change the periority of PendSV_IRQn to be equel the periorty of SysTick_IRQn
To Avoid Nesting Interrupt about this section of code
```
int main(void)
{
HW_init();
...
...
...
}
```
The big role of this function to change the periority of the PendSV_IRQn to be equel the periorty of SysTick_IRQn
```
__NVIC_SetPriority(PendSV_IRQn, 15);
```
This Operating System Based on ARM cortex M3 So if you want to Use This Operating System with another Microprocessor You will Change in this Function


## Second Step
Use MYRTOS_init() in main To Initailze Your RTOS
```
if(MYRTOS_init()!= NoError)
	while(1);
```
**We Use MYRTOS_init() Function To:**
1. Update OS Mode (OSsuspend)

We make the Operating System in **Suspend state** in the Beginning 
to Initalize All Parameter then make it in **Running State**

```OS_Control.OSmodeID = OSsuspend;```

2. Specify the main Stack for OS ```error +=MYRTOS_Create_MainStack();```
```
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
```
First _S_MSP_Task eqeul The Top of Stack "_estack --> we can get the symbol From LinkerScript File"<br/>
Then We Calculate End of Main Stack pointer by subtract Top of stack from MainStackSize "MainStackSize is Macro You Can Change Size by it "<br/>
Then Check if The End Of Main Stack Pointer Still in Stack Section not Enter Heap Section <br/>
Then Use PSP_Task_Locator to be equel _E_MSP_Task - 8 Byte <br/>
and this will be The first Location of Task1<br/>
![image](https://github.com/Ephraim-Hedia/Embedded_System_Diploma/assets/74508494/988cbbd4-c419-4969-bc40-1a7df53ce6b4)

3. Configure IDLE TASK

You Can See Below In the Third Step How to create Task
```
strcpy(MYRTOS_idleTask.TaskName,"idleTask");
MYRTOS_idleTask.priority =255;
MYRTOS_idleTask.p_TaskEntry=MYRTOS_IdleTask;
MYRTOS_idleTask.Stack_Size=300;

error += MYRTOS_CreateTask(&MYRTOS_idleTask);
```



## Third Step
To Create any Task You Need to Use This Stuct **Task_ref**

You will Use 4 Parameters Only From This Struct **Task_ref** and the another parameters The OS will Set them


```
typedef struct {
	unsigned int Stack_Size ;		  //Set By the User
	unsigned char priority ;		  //Set By the User
  char TaskName[30];				    //Set By the User
	void (*p_TaskEntry)(void); 		//Set By the User -- pointer to Task C Function


	unsigned int _S_PSP_TASK ; 		//Not Entered by the user //Calculate By OS
	unsigned int _E_PSP_TASK ;		//Not Entered by the user //Calculate By OS
	unsigned int * Current_PSP ;	//Not Entered by the user // To can return to the same address in this task //Calculate By OS	
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
```
These The 4 Parameters You will Use :
```
unsigned int Stack_Size ;	
unsigned char priority ;	
char TaskName[30];	
void (*p_TaskEntry)(void);
```
Stack_Size --> To Set the Task Stack size <br/>
priority --> To Set the Task Priority , and 0 Number a higher in  periority than 255 <br/>
char TaskName[30] --> You Can Write Here a breif of your Task "it can use for debugging" <br/>
void (*p_TaskEntry)(void) --> you Set this parameter with address of function  <br/>


### Example About How to Use MYRTOS_CreateTask()
```

  Task_ref Task1,Task2,Task3,Task4;
  Task1.Stack_Size=1000;
	Task1.p_TaskEntry=task1;
	Task1.priority=4;
	strcpy(Task1.TaskName ,"task_1");
	Task2.Stack_Size=1000;
	Task2.p_TaskEntry=task2;
	Task2.priority=3;
	strcpy(Task2.TaskName ,"task_2");

	Task3.Stack_Size=1000;
	Task3.p_TaskEntry=task3;
	Task3.priority=2;
	strcpy(Task3.TaskName ,"task_3");

	Task4.Stack_Size=1000;
	Task4.p_TaskEntry=task4;
	Task4.priority=1;
	strcpy(Task4.TaskName ,"task_4");

	error+=MYRTOS_CreateTask(&Task1);
	error+=MYRTOS_CreateTask(&Task2);
	error+=MYRTOS_CreateTask(&Task3);
	error+=MYRTOS_CreateTask(&Task4);
```




