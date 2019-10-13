CC=arm-none-eabi
MCPU=-mcpu=arm1176jzf-s
CFLAGS=-ffreestanding -nostdlib -Wall -Wextra -c
LDFLAGS=-nostdlib -lgcc

TARGET=kernel.img
ELF=kernel.elf
LINKER=linker.ld


$(TARGET): start.S main.c string.c string.h gpio.c gpio.h uart.c uart.h
	@echo " Compile\tstart.o"
	@$(CC)-gcc $(MCPU) $(CFLAGS) start.S -o start.o
	@echo " Compile\tmain.o"
	@$(CC)-gcc $(MCPU) $(CFLAGS) main.c -o main.o
	@echo " Compile\tuart.o"
	@$(CC)-gcc $(MCPU) $(CFLAGS) uart.c -o uart.o
	@echo " Compile\tgpio.o"
	@$(CC)-gcc $(MCPU) $(CFLAGS) gpio.c -o gpio.o
	@echo " Compile\tstring.o"
	@$(CC)-gcc $(MCPU) $(CFLAGS) string.c -o string.o
	@echo " Compile\t$(ELF)"
	@$(CC)-gcc -T $(LINKER) start.o main.o uart.o gpio.o string.o -o $(ELF) $(LDFLAGS)
	@echo " Create\t\t$(TARGET)"
	@$(CC)-objcopy $(ELF) -O binary $(TARGET)

clean:
	@echo " Clean"
	@rm -f $(TARGET) $(ELF) *.o
