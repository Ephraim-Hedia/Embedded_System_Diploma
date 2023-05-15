# ARM Coure Lesson 2

### Handler vs Thread Modes && privileged vs unprivileged Modes:
>The processor supports two modes of operation . **Thread mode and Handler Mode** .

```
the processor enters Thread mode on Reset , or as result of an exception return . 
privileged and Unprivileged code can run in Thread Mode

The processor enters Handler Mode as result of an exception. All code is privileged in Handler Mode
```


![1](https://github.com/Ephraim-Hedia/Embedded_System_Diploma/assets/74508494/8f56ebd5-b33b-482e-969e-c5123d3359af)
![2](https://github.com/Ephraim-Hedia/Embedded_System_Diploma/assets/74508494/83c3c474-8f2f-4862-be9f-6a73868ccd20)


### Thumb vs Debug State :
```
Debug state means the processor is halted 
but the Tumb mode means the normal mode --> the processor can work without any halt 
```
## Core registers :
>Overview for the Core Registers


![3](https://github.com/Ephraim-Hedia/Embedded_System_Diploma/assets/74508494/48a8100e-62d4-48f4-94cb-179ddbf205d0)

>Discribtion for the Registers


![4](https://github.com/Ephraim-Hedia/Embedded_System_Diploma/assets/74508494/eaee9842-9637-4404-b19c-766869e1dc44)


### R0-R12
General purpuse Register 
### MSP (Stack Pointer)

### PSP (Stack Pointer)
### LR  (Link Register)
### PC  (Program Counter)
### PSR (Program status register)
### ASPR (Application Program status register)
### IPSR (Interrupt Program status register)
### EPSR (Execution Program status register)
### PRIMASK (Priority mask register )
### FAULTMASK (Fault mask register)
### BASEPRI (Base priority mask register)
### Control Register

### Thumb , ARM , Thumb2 ISA

# The Main LAB

![6](https://github.com/Ephraim-Hedia/Embedded_System_Diploma/assets/74508494/001dfb7f-1b77-4f5d-b79c-1ee2f0872aec)

![7](https://github.com/Ephraim-Hedia/Embedded_System_Diploma/assets/74508494/9babdbdc-378e-49e1-b860-3470cf0a0c3d)




