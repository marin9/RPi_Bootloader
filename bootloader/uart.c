#include "rpi.h"

#define AUX_ENABLES			((volatile unsigned int*)(UART_BASE+0x04))
#define AUX_MU_IO_REG		((volatile unsigned int*)(UART_BASE+0x40))
#define AUX_MU_IER_REG		((volatile unsigned int*)(UART_BASE+0x44))
#define AUX_MU_IIR_REG		((volatile unsigned int*)(UART_BASE+0x48))
#define AUX_MU_LCR_REG		((volatile unsigned int*)(UART_BASE+0x4C))
#define AUX_MU_MCR_REG		((volatile unsigned int*)(UART_BASE+0x50))
#define AUX_MU_LSR_REG		((volatile unsigned int*)(UART_BASE+0x54))
#define AUX_MU_CNTL_REG		((volatile unsigned int*)(UART_BASE+0x60))
#define AUX_MU_BAUD_REG		((volatile unsigned int*)(UART_BASE+0x68))

#define GPFSEL1 			((volatile unsigned int*)(GPIO_BASE+0x04))
#define GPSET0  			((volatile unsigned int*)(GPIO_BASE+0x1C))
#define GPCLR0 				((volatile unsigned int*)(GPIO_BASE+0x28))
#define GPPUD				((volatile unsigned int*)(GPIO_BASE+0x94))
#define GPPUDCLK0			((volatile unsigned int*)(GPIO_BASE+0x98))


void uart_init() {
	uint i;

	*AUX_ENABLES = 1;     // enable mini uart
	*AUX_MU_IER_REG = 0;  // no interrupts
	*AUX_MU_CNTL_REG = 0; // cts/rts control... not used
	*AUX_MU_LCR_REG = 3;  // 8 bit mod
	*AUX_MU_MCR_REG = 0;  // rts signal to high
	*AUX_MU_IER_REG = 0;  // no interrupts
	*AUX_MU_IIR_REG = 0x6; // clear fifo
	*AUX_MU_BAUD_REG = 270;
	// set baud rate 115200 ((250,000,000/115200)/8)-1 = 270
	// no parity, 1 start bit, 1 stop bit, this is fixed

	// Set GPIO 14 and 15 to alt5 function
	gpio_mode(14, GPIO_FN5);
	gpio_mode(15, GPIO_FN5);

	*AUX_MU_CNTL_REG = 3; // Enable transmitter and receiver
	for (i = 0; i < 32; ++i)	// Empty input buffer
		*AUX_MU_IO_REG;
}

void uart_read(char *buff, uint len) {
	uint i;
	for (i = 0; i < len; ++i) {
		while (!(*AUX_MU_LSR_REG & 0x01));
		buff[i] = (unsigned char)((*AUX_MU_IO_REG) & 0xff);
	}
}

void uart_write(char *buff, uint len) {
	uint i;
	for (i = 0; i < len; ++i) {
		while (!(*AUX_MU_LSR_REG & 0x20));
		*AUX_MU_IO_REG = buff[i];
	}
	// flush
	while (!(*AUX_MU_LSR_REG & 0x40));
}
