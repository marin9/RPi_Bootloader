CC=arm-none-eabi
MCPU=-mcpu=arm1176jzf-s
CFLAGS=-nostdlib -ffreestanding -Wall -Wextra -O2
LDFLAGS=-nostdlib -lgcc

LINKER=linker.ld
ELF=kernel.elf
TARGET=../kernel.img

INC	:= $(wildcard *.h)
ASM	:= start.S
SRC	:= main.c
SRC	+= gpio.c
SRC	+= uart.c


OBJA	:= $(ASM:%.S=%.o)
OBJC	:= $(SRC:%.c=%.o)

$(TARGET): $(ELF)
	@echo " Create\t\t" $(TARGET)
	@$(CC)-objcopy $(ELF) -O binary $(TARGET)

$(ELF): $(LINKER) $(OBJA) $(OBJC)
	@echo " Linking\t" $(ELF)
	@$(CC)-gcc -T $(LINKER) $(OBJA) $(OBJC) -o $@ $(LDFLAGS)

$(OBJA): %.o : %.S $(INC)
	@echo " Compile\t" $<
	@$(CC)-gcc $(MCPU) $(CFLAGS) -c $< -o $@

$(OBJC): %.o : %.c $(INC)
	@echo " Compile\t" $<
	@$(CC)-gcc $(MCPU) $(CFLAGS) -c $< -o $@

clean:
	@echo "Clean"
	@-rm -rf *.o $(ELF) $(TARGET)
