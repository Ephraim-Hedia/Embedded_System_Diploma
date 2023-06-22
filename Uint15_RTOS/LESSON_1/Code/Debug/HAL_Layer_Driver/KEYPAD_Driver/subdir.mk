################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL_Layer_Driver/KEYPAD_Driver/keypad.c 

OBJS += \
./HAL_Layer_Driver/KEYPAD_Driver/keypad.o 

C_DEPS += \
./HAL_Layer_Driver/KEYPAD_Driver/keypad.d 


# Each subdirectory must supply rules for building sources it contributes
HAL_Layer_Driver/KEYPAD_Driver/keypad.o: ../HAL_Layer_Driver/KEYPAD_Driver/keypad.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I"D:/Learn_in_Depth/Embedded_C_Workspace/RTOS_Lesson_1/CMSIS_V5" -I../Inc -I"D:/Learn_in_Depth/Embedded_C_Workspace/RTOS_Lesson_1/HAL_Layer_Driver/inc" -I"D:/Learn_in_Depth/Embedded_C_Workspace/RTOS_Lesson_1/STM32_F103C6_Drivers/inc" -I"D:/Learn_in_Depth/Embedded_C_Workspace/RTOS_Lesson_1/MY_RTOS/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"HAL_Layer_Driver/KEYPAD_Driver/keypad.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

