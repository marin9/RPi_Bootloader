# Bootloader for Raspberry Pi Zero

Run program on Raspberry Pi over UART, instead of removing, writing, and replacing
the SD card numerous times.

**Usage:**
* 1) run compile.sh: ./compile.sh
* 2) put bootcode.bin, start.elf and kernel.img on SD card
* 3) insert SD card into RPi and restart it
* 4) run rpiloader : sudo ./rpiloader /dev/ttyUSB0 prog

