################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MY_RTOS/CortexMX_OS_porting.c \
../MY_RTOS/MYRTOS_FIFO.c \
../MY_RTOS/Scheduler.c 

OBJS += \
./MY_RTOS/CortexMX_OS_porting.o \
./MY_RTOS/MYRTOS_FIFO.o \
./MY_RTOS/Scheduler.o 

C_DEPS += \
./MY_RTOS/CortexMX_OS_porting.d \
./MY_RTOS/MYRTOS_FIFO.d \
./MY_RTOS/Scheduler.d 


# Each subdirectory must supply rules for building sources it contributes
MY_RTOS/CortexMX_OS_porting.o: ../MY_RTOS/CortexMX_OS_porting.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/Learn_in_Depth/Embedded_C_Workspace/RTOS_Lesson_2/CMSIS_V5" -I"D:/Learn_in_Depth/Embedded_C_Workspace/RTOS_Lesson_2/HAL_Layer_Driver/inc" -I"D:/Learn_in_Depth/Embedded_C_Workspace/RTOS_Lesson_2/MY_RTOS/inc" -I"D:/Learn_in_Depth/Embedded_C_Workspace/RTOS_Lesson_2/STM32_F103C6_Drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"MY_RTOS/CortexMX_OS_porting.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
MY_RTOS/MYRTOS_FIFO.o: ../MY_RTOS/MYRTOS_FIFO.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/Learn_in_Depth/Embedded_C_Workspace/RTOS_Lesson_2/CMSIS_V5" -I"D:/Learn_in_Depth/Embedded_C_Workspace/RTOS_Lesson_2/HAL_Layer_Driver/inc" -I"D:/Learn_in_Depth/Embedded_C_Workspace/RTOS_Lesson_2/MY_RTOS/inc" -I"D:/Learn_in_Depth/Embedded_C_Workspace/RTOS_Lesson_2/STM32_F103C6_Drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"MY_RTOS/MYRTOS_FIFO.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
MY_RTOS/Scheduler.o: ../MY_RTOS/Scheduler.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/Learn_in_Depth/Embedded_C_Workspace/RTOS_Lesson_2/CMSIS_V5" -I"D:/Learn_in_Depth/Embedded_C_Workspace/RTOS_Lesson_2/HAL_Layer_Driver/inc" -I"D:/Learn_in_Depth/Embedded_C_Workspace/RTOS_Lesson_2/MY_RTOS/inc" -I"D:/Learn_in_Depth/Embedded_C_Workspace/RTOS_Lesson_2/STM32_F103C6_Drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"MY_RTOS/Scheduler.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

