CC=arm-none-eabi
MCPU=-mcpu=arm1176jzf-s
CFLAGS=-ffreestanding -nostdlib -Wall -Wextra -c
LDFLAGS=-nostdlib -lgcc

TARGET=example.img
ELF=example.elf
LINKER=linker.ld

$(TARGET): start.s main.c gpio.c gpio.h linker.ld
	$(CC)-gcc $(MCPU) $(CFLAGS) start.s -o start.o
	$(CC)-gcc $(MCPU) $(CFLAGS) main.c -o main.o
	$(CC)-gcc $(MCPU) $(CFLAGS) gpio.c -o gpio.o
	$(CC)-gcc -T $(LINKER) start.o main.o gpio.o -o $(ELF) $(LDFLAGS)
	$(CC)-objcopy $(ELF) -O binary $(TARGET)

clean:
	rm -f *.o
	rm -f $(ELF)
	rm -f $(TARGET)
