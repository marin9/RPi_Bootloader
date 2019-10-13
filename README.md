# Bootloader for Raspberry Pi Zero

Run program on Raspberry Pi over UART, instead of removing, writing, and replacing
the SD card numerous times. Bootloader will write program into RAM at address 0x10000, so you need to set this address into linker script instead of 0x8000.

**Usage:**
1) compile:
```c
make
```
2) put bootcode.bin, start.elf and kernel.img on SD card
3) insert SD card into RPi
4) restart RPi
5) boot program:
```c
sudo ./rpiloader -s /dev/ttyUSB0 -i example.img
```
For next boot you need to repeat only steps 4 and 5.

