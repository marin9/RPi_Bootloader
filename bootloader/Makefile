CC=arm-none-eabi
MCPU=-mcpu=arm1176jzf-s
CFLAGS=-ffreestanding -nostdlib -Wall -Wextra -c
LDFLAGS=-nostdlib -lgcc

TARGET=kernel.img
ELF=kernel.elf
LINKER=linker.ld


$(TARGET): start.c main.c gpio.c uart.c rpi.h
	@echo " Compile\tstart.o"
	@$(CC)-gcc $(MCPU) $(CFLAGS) start.c -o start.o
	@echo " Compile\tmain.o"
	@$(CC)-gcc $(MCPU) $(CFLAGS) main.c -o main.o
	@echo " Compile\tuart.o"
	@$(CC)-gcc $(MCPU) $(CFLAGS) uart.c -o uart.o
	@echo " Compile\tgpio.o"
	@$(CC)-gcc $(MCPU) $(CFLAGS) gpio.c -o gpio.o
	@echo " Compile\t$(ELF)"
	@$(CC)-gcc -T $(LINKER) start.o main.o uart.o gpio.o -o $(ELF) $(LDFLAGS)
	@echo " Create\t\t$(TARGET)"
	@$(CC)-objcopy $(ELF) -O binary $(TARGET)

clean:
	@echo " Clean"
	@rm -f $(TARGET) $(ELF) *.o
