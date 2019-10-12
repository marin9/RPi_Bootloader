#! /bin/bash

if [ $1 = "clean" ]; then
	cd bootloader
	make clean
	cd ../serial
	make clean
	cd ../example
	make clean
	cd ..

	rm *.img
	rm rpiloader

elif [ $1 = "start" ]; then
	cd bootloader
	make
	cd ../serial
	make
	cd ../example
	make
	cd ..

	cp bootloader/kernel.img kernel.img
	cp serial/rpiloader rpiloader
	cp example/example.img example.img
	sudo ./rpiloader -i example.img

else
	cd bootloader
	make
	cd ../serial
	make
	cd ../example
	make
	cd ..

	cp bootloader/kernel.img kernel.img
	cp serial/rpiloader rpiloader
	cp example/example.img example.img

	echo ""
	echo "1) Put bootcode.bin, start.elf, kernel.img"
	echo "   to SD card"
	echo "2) Insert SD card to RPi and restart it"
	echo "3) Start rpiloader:"
	echo "      sudo ./rpiloader"
	echo ""
fi

