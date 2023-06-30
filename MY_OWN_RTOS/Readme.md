# How to Use This RTOS


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
Stack_Size --> To Set the Task Stack size 

priority --> To Set the Task Priority , and 0 Number a higher in  periority than 255

char TaskName[30] --> You Can Write Here a breif of your Task "it can use for debugging"

void (*p_TaskEntry)(void) --> you Set this parameter with address of function 


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




