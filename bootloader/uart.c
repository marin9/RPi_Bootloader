#include "uart.h"

#define RPI_PERIPHERAL_ADDR 0x20000000
#define UART_ADDR			(RPI_PERIPHERAL_ADDR+0x215000)
#define GPIO_ADDR			(RPI_PERIPHERAL_ADDR+0x200000)

#define AUX_ENABLES			((volatile unsigned int*)(UART_ADDR+0x04))
#define AUX_MU_IO_REG		((volatile unsigned int*)(UART_ADDR+0x40))
#define AUX_MU_IER_REG		((volatile unsigned int*)(UART_ADDR+0x44))
#define AUX_MU_IIR_REG		((volatile unsigned int*)(UART_ADDR+0x48))
#define AUX_MU_LCR_REG		((volatile unsigned int*)(UART_ADDR+0x4C))
#define AUX_MU_MCR_REG		((volatile unsigned int*)(UART_ADDR+0x50))
#define AUX_MU_LSR_REG		((volatile unsigned int*)(UART_ADDR+0x54))
#define AUX_MU_MSR_REG		((volatile unsigned int*)(UART_ADDR+0x58))
#define AUX_MU_SCRATCH		((volatile unsigned int*)(UART_ADDR+0x5C))
#define AUX_MU_CNTL_REG		((volatile unsigned int*)(UART_ADDR+0x60))
#define AUX_MU_STAT_REG		((volatile unsigned int*)(UART_ADDR+0x64))
#define AUX_MU_BAUD_REG		((volatile unsigned int*)(UART_ADDR+0x68))

#define GPFSEL1 			((volatile unsigned int*)(GPIO_ADDR+0x04))
#define GPSET0  			((volatile unsigned int*)(GPIO_ADDR+0x1C))
#define GPCLR0 				((volatile unsigned int*)(GPIO_ADDR+0x28))
#define GPPUD				((volatile unsigned int*)(GPIO_ADDR+0x94))
#define GPPUDCLK0			((volatile unsigned int*)(GPIO_ADDR+0x98))




void uart_init(){
	int i, ra;

	*AUX_ENABLES=1;     // enable mini uart
	*AUX_MU_IER_REG=0;  // no interrupts
	*AUX_MU_CNTL_REG=0; // cts/rts control... not used
	*AUX_MU_LCR_REG=3;  // 8 bit mod
	*AUX_MU_MCR_REG=0;  // rts signal to high
	*AUX_MU_IER_REG=0;  // no interrupts
	*AUX_MU_IIR_REG=0x6; // clear fifo
	*AUX_MU_BAUD_REG=270; // set baud rate 115200 ((250,000,000/115200)/8)-1 = 270
	//no parity, 1 start bit, 1 stop bit, this is fixed

	// Set GPIO 14 and 15 to alt5 function
	ra=*GPFSEL1;
	ra&=~(7<<12); //gpio14
	ra|=2<<12;    //alt5
	ra&=~(7<<15); //gpio15
	ra|=2<<15;    //alt5
	*GPFSEL1=ra;

	*GPPUD=0;
	for(ra=0;ra<200;ra++)
		asm volatile ("nop");
	*GPPUDCLK0=(1<<14)|(1<<15);
	for(ra=0;ra<200;ra++)
		asm volatile ("nop");
	*GPPUDCLK0=0;

	*AUX_MU_CNTL_REG=3; // Enable transmitter and receiver
	for(i=0;i<32;++i){	// Empty input buffer
		ra=*AUX_MU_IO_REG;
	}
}

void uart_send(void *buf, int len){
	int i;
	unsigned char *c=(unsigned char*)buf;

	for(i=0;i<len;++i){
		while(!(*AUX_MU_LSR_REG & 0x20));
		*AUX_MU_IO_REG=c[i];
	}

	// flush
	while(!(*AUX_MU_LSR_REG & 0x40));
}

void uart_recv(void *buf, int len){
	int i;
	unsigned char *c=(unsigned char*)buf;

	for(i=0;i<len;++i){
		while(!(*AUX_MU_LSR_REG & 0x01));
		c[i]=(unsigned char)((*AUX_MU_IO_REG)&0xff);
	}
}
