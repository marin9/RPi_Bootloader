CC=arm-none-eabi
MCPU=-mcpu=arm1176jzf-s
CFLAGS=-nostdlib -ffreestanding -Wall -Wextra
LDFLAGS=-nostdlib -lgcc

LINKER=linker.ld
ELF=kernel.elf
TARGET=../kernel.img

INC	:= $(wildcard *.h)
SRC := $(wildcard *.c)
OBJ	:= $(SRC:%.c=%.o)

$(TARGET): $(ELF)
	@echo " Create\t\t" $(TARGET)
	@$(CC)-objcopy $(ELF) -O binary $(TARGET)

$(ELF): $(LINKER) $(OBJ)
	@echo " Linking\t" $(ELF)
	@$(CC)-gcc -T $(LINKER) $(OBJ) -o $@ $(LDFLAGS)

$(OBJ): %.o : %.c $(INC)
	@echo " Compile\t" $<
	@$(CC)-gcc $(MCPU) $(CFLAGS) -c $< -o $@

clean:
	@echo "Clean"
	@-rm -rf *.o $(ELF) $(TARGET)
