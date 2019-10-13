CC=arm-none-eabi
MCPU=-mcpu=arm1176jzf-s
CFLAGS=-ffreestanding -nostdlib -Wall -Wextra -c
LDFLAGS=-nostdlib -lgcc

TARGET=kernel.img
ELF=kernel.elf
LINKER=linker.ld


$(TARGET): start.S main.c gpio.c gpio.h linker.ld
	@echo " Compile\tstart.o"
	@$(CC)-gcc $(MCPU) $(CFLAGS) start.S -o start.o
	@echo " Compile\tmain.o"
	@$(CC)-gcc $(MCPU) $(CFLAGS) main.c -o main.o
	@echo " Compile\tgpio.o"
	@$(CC)-gcc $(MCPU) $(CFLAGS) gpio.c -o gpio.o
	@echo " Compile\t$(ELF)"
	@$(CC)-gcc -T $(LINKER) start.o main.o gpio.o -o $(ELF) $(LDFLAGS)
	@echo " Create\t\t$(TARGET)"
	@$(CC)-objcopy $(ELF) -O binary $(TARGET)

clean:
	@echo " Clean"
	@rm -f $(TARGET) $(ELF) *.o
