################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include STM32_F103C6_Drivers/subdir.mk
-include MY_RTOS/subdir.mk
-include HAL_Layer_Driver/LCD_Driver/subdir.mk
-include HAL_Layer_Driver/KEYPAD_Driver/subdir.mk
-include HAL_Layer_Driver/I2C_EEPROM_Slave/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
RTOS_Lesson_1.axf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
RTOS_Lesson_1.list \

OBJCOPY_BIN += \
RTOS_Lesson_1.bin \


# All Target
all: RTOS_Lesson_1.axf secondary-outputs

# Tool invocations
RTOS_Lesson_1.axf: $(OBJS) $(USER_OBJS) D:\Learn_in_Depth\Embedded_C_Workspace\RTOS_Lesson_1\STM32F103C6TX_FLASH.ld
	arm-none-eabi-gcc -gdwarf-2 -o "RTOS_Lesson_1.axf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"D:\Learn_in_Depth\Embedded_C_Workspace\RTOS_Lesson_1\STM32F103C6TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="RTOS_Lesson_1.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

RTOS_Lesson_1.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "RTOS_Lesson_1.list"
	@echo 'Finished building: $@'
	@echo ' '

RTOS_Lesson_1.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "RTOS_Lesson_1.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
