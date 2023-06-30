################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL_Layer_Driver/LCD_Driver/lcd.c 

OBJS += \
./HAL_Layer_Driver/LCD_Driver/lcd.o 

C_DEPS += \
./HAL_Layer_Driver/LCD_Driver/lcd.d 


# Each subdirectory must supply rules for building sources it contributes
HAL_Layer_Driver/LCD_Driver/lcd.o: ../HAL_Layer_Driver/LCD_Driver/lcd.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/Learn_in_Depth/Embedded_C_Workspace/RTOS_Part4_5/CMSIS_V5" -I"D:/Learn_in_Depth/Embedded_C_Workspace/RTOS_Part4_5/HAL_Layer_Driver/inc" -I"D:/Learn_in_Depth/Embedded_C_Workspace/RTOS_Part4_5/MY_RTOS/inc" -I"D:/Learn_in_Depth/Embedded_C_Workspace/RTOS_Part4_5/STM32_F103C6_Drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"HAL_Layer_Driver/LCD_Driver/lcd.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

