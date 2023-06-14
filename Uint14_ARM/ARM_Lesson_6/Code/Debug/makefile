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
ARM_Lesson_6.axf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
ARM_Lesson_6.list \

OBJCOPY_BIN += \
ARM_Lesson_6.bin \


# All Target
all: ARM_Lesson_6.axf secondary-outputs

# Tool invocations
ARM_Lesson_6.axf: $(OBJS) $(USER_OBJS) D:\Learn_in_Depth\Embedded_C_Workspace\ARM_Lesson_6\STM32F103C6TX_FLASH.ld
	arm-none-eabi-gcc -o "ARM_Lesson_6.axf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"D:\Learn_in_Depth\Embedded_C_Workspace\ARM_Lesson_6\STM32F103C6TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="ARM_Lesson_6.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

ARM_Lesson_6.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "ARM_Lesson_6.list"
	@echo 'Finished building: $@'
	@echo ' '

ARM_Lesson_6.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "ARM_Lesson_6.bin"
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
