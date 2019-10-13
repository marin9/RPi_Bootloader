all: bootloader example serial
	$(MAKE) -C bootloader
	$(MAKE) -C example
	$(MAKE) -C serial

clean:
	$(MAKE) -C bootloader clean
	$(MAKE) -C example clean
	$(MAKE) -C serial clean
