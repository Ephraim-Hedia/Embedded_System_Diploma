################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL_Layer_Driver/I2C_EEPROM_Slave/I2C_EEPROM_Slave.c 

OBJS += \
./HAL_Layer_Driver/I2C_EEPROM_Slave/I2C_EEPROM_Slave.o 

C_DEPS += \
./HAL_Layer_Driver/I2C_EEPROM_Slave/I2C_EEPROM_Slave.d 


# Each subdirectory must supply rules for building sources it contributes
HAL_Layer_Driver/I2C_EEPROM_Slave/I2C_EEPROM_Slave.o: ../HAL_Layer_Driver/I2C_EEPROM_Slave/I2C_EEPROM_Slave.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/Learn_in_Depth/Embedded_C_Workspace/ARM_Lesson_6/CMSIS_V5" -I"D:/Learn_in_Depth/Embedded_C_Workspace/ARM_Lesson_6/STM32_F103C6_Drivers/inc" -I"D:/Learn_in_Depth/Embedded_C_Workspace/ARM_Lesson_6/HAL_Layer_Driver/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"HAL_Layer_Driver/I2C_EEPROM_Slave/I2C_EEPROM_Slave.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

