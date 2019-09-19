CC=arm-none-eabi
CFLAGS=-mcpu=arm1176jzf-s -ffreestanding -nostdlib -Wall -Wextra -c
LDFLAGS=-nostdlib -lgcc


ELF=kernel.elf
TARGET=kernel.img


all: $(TARGET)

clean:
	rm -f *.o
	rm -f $(ELF)
	rm -f $(TARGET)

$(TARGET): start.s main.c string.c string.h gpio.c gpio.h uart.c uart.h
	$(CC)-gcc $(CFLAGS) string.c -o string.o
	$(CC)-gcc $(CFLAGS) start.s -o start.o
	$(CC)-gcc $(CFLAGS) main.c -o main.o
	$(CC)-gcc $(CFLAGS) uart.c -o uart.o
	$(CC)-gcc $(CFLAGS) gpio.c -o gpio.o
	$(CC)-gcc -T linker.ld start.o main.o uart.o gpio.o string.o -o $(ELF) $(LDFLAGS)
	$(CC)-objcopy $(ELF) -O binary $(TARGET)

