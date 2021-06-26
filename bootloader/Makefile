CC			= arm-none-eabi
MCPU		= -mcpu=arm1176jzf-s
CFLAGS		= -ffreestanding -Wall -Wextra -O2 -I.
LDFLAGS		= -nostdlib
LINKER		= linker.ld
TARGET		= ../kernel

INC			:= $(wildcard *.h)
ASM 		:= $(wildcard *.s)
SRC 		:= $(wildcard *.c)
OBJA		:= $(ASM:%.s=%.o)
OBJC		:= $(SRC:%.c=%.o)


$(TARGET): $(LINKER) $(OBJA) $(OBJC)
	@echo " Create\t\t" $(TARGET).img
	@$(CC)-gcc -T $(LINKER) $(OBJA) $(OBJC) -o $(TARGET).elf $(LDFLAGS)
	@$(CC)-objcopy $(TARGET).elf -O binary $(TARGET).img

$(OBJA): %.o : %.s $(INC)
	@echo " Compile\t" $<
	@$(CC)-gcc $(MCPU) $(CFLAGS) -c $< -o $@

$(OBJC): %.o : %.c $(INC)
	@echo " Compile\t" $<
	@$(CC)-gcc $(MCPU) $(CFLAGS) -c $< -o $@

clean:
	@echo " Clean"
	@-rm -rf *.o $(TARGET).*
