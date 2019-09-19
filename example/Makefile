CC=arm-none-eabi
CFLAGS=-mcpu=arm1176jzf-s -ffreestanding -nostdlib -Wall -Wextra -c
LDFLAGS=-nostdlib -lgcc


TARGET=prog
ELF=prog.elf
LINKER=linker.ld


all: $(TARGET)

clean:
	rm -f *.o
	rm -f $(ELF)
	rm -f $(TARGET)

$(TARGET): start.s main.c gpio.c gpio.h linker.ld
	$(CC)-gcc $(CFLAGS) start.s -o start.o
	$(CC)-gcc $(CFLAGS) main.c -o main.o
	$(CC)-gcc $(CFLAGS) gpio.c -o gpio.o
	$(CC)-gcc -T $(LINKER) start.o main.o gpio.o -o $(ELF) $(LDFLAGS)
	$(CC)-objcopy $(ELF) -O binary $(TARGET)

