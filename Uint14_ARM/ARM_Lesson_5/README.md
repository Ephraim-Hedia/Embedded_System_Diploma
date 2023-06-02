# ARM LESSON 5
## AIM of LAB
> WE Want to make Simple OS , its freature to switch between privileged and unprivileged Access and can switch between MSP and PSP . 
> 
> we replace ticker with EXTI rising edge in PIN9 , and we make two Tasks Only --> **TaskA and TaskB** .
> 
> by default the OS doesn't execute anything till rising edge to PIN9 to make EXTI .
## Table of Content 
### 1-How to Calculate the top of MSP 
![1](https://github.com/Ephraim-Hedia/Embedded_System_Diploma/assets/74508494/aa4bad69-48cf-459c-94f7-b66e34fd83df)

### 2-Calculation of Memory bountries 
![2](https://github.com/Ephraim-Hedia/Embedded_System_Diploma/assets/74508494/0ef88997-f4a9-43a6-a76c-975f9addf5c7)


### 3-OS doesn't execute TASKA of TASKB untill EXTI take place
### 3.1
![3](https://github.com/Ephraim-Hedia/Embedded_System_Diploma/assets/74508494/943da704-824a-4dd2-915a-79da91abb44f)
### 3.2
![4](https://github.com/Ephraim-Hedia/Embedded_System_Diploma/assets/74508494/ca751f16-1984-41b0-a4d8-0eafb44c7b03)
### 4- Put value to PSP 
![5](https://github.com/Ephraim-Hedia/Embedded_System_Diploma/assets/74508494/e3c9868f-d705-44ea-8fe0-b6cd75162476)

### 5- Use PSP as SP 
![6](https://github.com/Ephraim-Hedia/Embedded_System_Diploma/assets/74508494/6ffc0344-7501-48f5-b5a4-c40fba7d324e)

### 6- Processor take unprivileged Access to prevent Tasks to change in OS 
![7](https://github.com/Ephraim-Hedia/Embedded_System_Diploma/assets/74508494/3709f602-bb4b-4051-952a-b6e2470a5287)

### 7- Context Switching to TaskA Function
### 7.1
![8](https://github.com/Ephraim-Hedia/Embedded_System_Diploma/assets/74508494/2f0c6ef1-3770-43be-a147-852006f2fcce)
### 7.2
![9](https://github.com/Ephraim-Hedia/Embedded_System_Diploma/assets/74508494/0fee2a8e-a55d-4a7c-baa1-6723943ce410)

### 8- Make the processor have privileged Access Again 
 ![10](https://github.com/Ephraim-Hedia/Embedded_System_Diploma/assets/74508494/8d9755f5-cd80-4fc8-afd3-aeaf76184ead)

### 9- Using MSP Again
![11](https://github.com/Ephraim-Hedia/Embedded_System_Diploma/assets/74508494/4b572bc2-73ad-4d75-884a-956f331266bb)
