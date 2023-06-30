# Examples On how to simulate My Own RTOS 

### Idle Task
This Task will be occur if No Tasks Activate in Our RTOS 
![1_Idle Task](https://github.com/Ephraim-Hedia/Embedded_System_Diploma/assets/74508494/b35ad0df-121c-4ae5-b3ec-9cb033b76af1)


### Round Robin Algorithm
This Mechanism we will Use if we activate More than Task in Our Operating System 
and this Mechanism will make the tasks operate Together withen specific Period
![2_Round Robin Algorithm](https://github.com/Ephraim-Hedia/Embedded_System_Diploma/assets/74508494/cd5109c1-35d6-4fc5-a060-e54a2aa0db3d)


### Preemptive based on priority
This Mechanism manage the Operating System if more than Task Acctivate
So the Highest periority will be run 
![3_Preemptive based on priority](https://github.com/Ephraim-Hedia/Embedded_System_Diploma/assets/74508494/3b517f55-ee8e-4e19-9ccb-ee04e08015eb)

### Task Wait Function
This Mechanism if You want to make the task Run after specific Time 
so You will Use this Function to do that

### T4 Priority > T3  Priority  > T2 Priority  > T1 Priority 
This Lab to tread with tasks priority and use Activate and Terminate Functions
![5_T4 Priority bigger Than T3  Priority  bigger Than T2 Priority  bigger Than T1 Priority](https://github.com/Ephraim-Hedia/Embedded_System_Diploma/assets/74508494/37e74cec-94a1-4444-a321-2c0bdca468f1)


### Priority inversion Issue
This Lab to Use accure Mutex Function 
and Try to make Task1 which has "Lowest periorty" accure the mutex 
and the Task4 Which has "Highest periorty" try to Accure the Mutex --> SO Task 4 will be blocked till Task1 release the mutex 
![6_Priority inversion](https://github.com/Ephraim-Hedia/Embedded_System_Diploma/assets/74508494/133d0665-fe20-46d6-9530-3fc256e392e1)


### Dead lock






