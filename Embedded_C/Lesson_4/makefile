#@Copyright : Guiguis Hedia

CC=arm-none-eabi-
CFLAGS=-gdwarf-2 -mcpu=cortex-m4 -g
INCS=-I .
LIBS=
SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)
As= $(wildcard *.s)
AsOBJ= $(As:.s=.o)

Project_Name=Unit3_lab4_CortexM4

all: $(Project_Name).bin
	@echo "============Build is Done============"
#startup.o: startup.s
#	$(CC)as.exe $(CFLAGS) $< -o $@
	
%.o: %.c
	$(CC)gcc.exe -c $(CFLAGS) $(INCS) $< -o $@
	
	
$(Project_Name).elf: $(OBJ) $(AsOBJ)
	$(CC)ld.exe -T linker_script.ld $(LIBS) $(OBJ) $(AsOBJ) -o $@ -Map=Map_file.map
	cp $(Project_Name).elf $(Project_Name).axf	
$(Project_Name).bin: $(Project_Name).elf 
	
	$(CC)objcopy.exe -O binary $< $@
	
clean_all:
		rm *.o *.elf *.bin 

clean:
		rm *.elf *.bin 