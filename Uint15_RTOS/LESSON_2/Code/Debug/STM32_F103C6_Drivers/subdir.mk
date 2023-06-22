################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../STM32_F103C6_Drivers/STM32_F103C6_EXTI_Driver.c \
../STM32_F103C6_Drivers/STM32_F103C6_GPIO_Driver.c \
../STM32_F103C6_Drivers/STM32_F103C6_I2C_Driver.c \
../STM32_F103C6_Drivers/STM32_F103C6_RCC_Driver.c \
../STM32_F103C6_Drivers/STM32_F103C6_SPI_Driver.c \
../STM32_F103C6_Drivers/STM32_F103C6_USART_Driver.c 

OBJS += \
./STM32_F103C6_Drivers/STM32_F103C6_EXTI_Driver.o \
./STM32_F103C6_Drivers/STM32_F103C6_GPIO_Driver.o \
./STM32_F103C6_Drivers/STM32_F103C6_I2C_Driver.o \
./STM32_F103C6_Drivers/STM32_F103C6_RCC_Driver.o \
./STM32_F103C6_Drivers/STM32_F103C6_SPI_Driver.o \
./STM32_F103C6_Drivers/STM32_F103C6_USART_Driver.o 

C_DEPS += \
./STM32_F103C6_Drivers/STM32_F103C6_EXTI_Driver.d \
./STM32_F103C6_Drivers/STM32_F103C6_GPIO_Driver.d \
./STM32_F103C6_Drivers/STM32_F103C6_I2C_Driver.d \
./STM32_F103C6_Drivers/STM32_F103C6_RCC_Driver.d \
./STM32_F103C6_Drivers/STM32_F103C6_SPI_Driver.d \
./STM32_F103C6_Drivers/STM32_F103C6_USART_Driver.d 


# Each subdirectory must supply rules for building sources it contributes
STM32_F103C6_Drivers/STM32_F103C6_EXTI_Driver.o: ../STM32_F103C6_Drivers/STM32_F103C6_EXTI_Driver.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/Learn_in_Depth/Embedded_C_Workspace/RTOS_Lesson_2/CMSIS_V5" -I"D:/Learn_in_Depth/Embedded_C_Workspace/RTOS_Lesson_2/HAL_Layer_Driver/inc" -I"D:/Learn_in_Depth/Embedded_C_Workspace/RTOS_Lesson_2/MY_RTOS/inc" -I"D:/Learn_in_Depth/Embedded_C_Workspace/RTOS_Lesson_2/STM32_F103C6_Drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"STM32_F103C6_Drivers/STM32_F103C6_EXTI_Driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
STM32_F103C6_Drivers/STM32_F103C6_GPIO_Driver.o: ../STM32_F103C6_Drivers/STM32_F103C6_GPIO_Driver.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/Learn_in_Depth/Embedded_C_Workspace/RTOS_Lesson_2/CMSIS_V5" -I"D:/Learn_in_Depth/Embedded_C_Workspace/RTOS_Lesson_2/HAL_Layer_Driver/inc" -I"D:/Learn_in_Depth/Embedded_C_Workspace/RTOS_Lesson_2/MY_RTOS/inc" -I"D:/Learn_in_Depth/Embedded_C_Workspace/RTOS_Lesson_2/STM32_F103C6_Drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"STM32_F103C6_Drivers/STM32_F103C6_GPIO_Driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
STM32_F103C6_Drivers/STM32_F103C6_I2C_Driver.o: ../STM32_F103C6_Drivers/STM32_F103C6_I2C_Driver.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/Learn_in_Depth/Embedded_C_Workspace/RTOS_Lesson_2/CMSIS_V5" -I"D:/Learn_in_Depth/Embedded_C_Workspace/RTOS_Lesson_2/HAL_Layer_Driver/inc" -I"D:/Learn_in_Depth/Embedded_C_Workspace/RTOS_Lesson_2/MY_RTOS/inc" -I"D:/Learn_in_Depth/Embedded_C_Workspace/RTOS_Lesson_2/STM32_F103C6_Drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"STM32_F103C6_Drivers/STM32_F103C6_I2C_Driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
STM32_F103C6_Drivers/STM32_F103C6_RCC_Driver.o: ../STM32_F103C6_Drivers/STM32_F103C6_RCC_Driver.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/Learn_in_Depth/Embedded_C_Workspace/RTOS_Lesson_2/CMSIS_V5" -I"D:/Learn_in_Depth/Embedded_C_Workspace/RTOS_Lesson_2/HAL_Layer_Driver/inc" -I"D:/Learn_in_Depth/Embedded_C_Workspace/RTOS_Lesson_2/MY_RTOS/inc" -I"D:/Learn_in_Depth/Embedded_C_Workspace/RTOS_Lesson_2/STM32_F103C6_Drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"STM32_F103C6_Drivers/STM32_F103C6_RCC_Driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
STM32_F103C6_Drivers/STM32_F103C6_SPI_Driver.o: ../STM32_F103C6_Drivers/STM32_F103C6_SPI_Driver.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/Learn_in_Depth/Embedded_C_Workspace/RTOS_Lesson_2/CMSIS_V5" -I"D:/Learn_in_Depth/Embedded_C_Workspace/RTOS_Lesson_2/HAL_Layer_Driver/inc" -I"D:/Learn_in_Depth/Embedded_C_Workspace/RTOS_Lesson_2/MY_RTOS/inc" -I"D:/Learn_in_Depth/Embedded_C_Workspace/RTOS_Lesson_2/STM32_F103C6_Drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"STM32_F103C6_Drivers/STM32_F103C6_SPI_Driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
STM32_F103C6_Drivers/STM32_F103C6_USART_Driver.o: ../STM32_F103C6_Drivers/STM32_F103C6_USART_Driver.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/Learn_in_Depth/Embedded_C_Workspace/RTOS_Lesson_2/CMSIS_V5" -I"D:/Learn_in_Depth/Embedded_C_Workspace/RTOS_Lesson_2/HAL_Layer_Driver/inc" -I"D:/Learn_in_Depth/Embedded_C_Workspace/RTOS_Lesson_2/MY_RTOS/inc" -I"D:/Learn_in_Depth/Embedded_C_Workspace/RTOS_Lesson_2/STM32_F103C6_Drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"STM32_F103C6_Drivers/STM32_F103C6_USART_Driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

