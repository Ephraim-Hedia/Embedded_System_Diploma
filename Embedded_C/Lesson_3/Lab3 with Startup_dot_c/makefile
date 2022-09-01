#@Copyright : Guiguis Hedia

CC=arm-none-eabi-
CFLAG=-gdwarf-2 -mcpu=cortex-m3
INCS=-I .
LIBS=
SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)
As= $(wildcard *.s)
AsOBJ= $(As:.s=.o)

Project_Name=learn_in_depth_cortex_m3

all: $(Project_Name).bin
	@echo "============Build is Done============"
#startup.o: startup.s
#	$(CC)as.exe $(CFLAGS) $< -o $@
	
%.o: %.c
	$(CC)gcc.exe -c $(CFLAGS) $(INCS) $< -o $@
	
	
$(Project_Name).elf: $(OBJ) $(AsOBJ)
	$(CC)ld.exe -T linker_script.ld $(LIBS) $(OBJ) $(AsOBJ) -o $@ -Map=Map_file.map
	
$(Project_Name).bin: $(Project_Name).elf 
	
	$(CC)objcopy.exe -O binary $< $@
	
clean_all:
		rm *.o *.elf *.bin 

clean:
		rm *.elf *.bin 