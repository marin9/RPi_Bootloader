#include "rpi.h"

#define UART_DR		((volatile uint*)(UART_BASE + 0x00))
#define UART_FR		((volatile uint*)(UART_BASE + 0x18))
#define UART_IBRD	((volatile uint*)(UART_BASE + 0x24))
#define UART_FBRD	((volatile uint*)(UART_BASE + 0x28))
#define UART_LCRH	((volatile uint*)(UART_BASE + 0x2C))
#define UART_CR		((volatile uint*)(UART_BASE + 0x30))
#define UART_ICR	((volatile uint*)(UART_BASE + 0x44))

#define CR_EN		(1 << 0)
#define CR_RXEN		(1 << 7)
#define CR_TXEN		(1 << 8)
#define FR_RXFE		(1 << 4)
#define FR_TXFF		(1 << 5)
#define FR_TXFE		(1 << 7)
#define LCRH_ENFIFO (1 << 4)
#define LCRH_WLEN8	(3 << 5)


void uart_init(uint br){
	*UART_CR=0;
	gpio_mode(14, GPIO_FN0);
	gpio_mode(15, GPIO_FN0);
    *UART_ICR=0x7FF;

    switch(br){
    case 9600:
    	*UART_IBRD=325;
    	*UART_FBRD=33;
    	break;
    case 19200:
       	*UART_IBRD=162;
    	*UART_FBRD=49;
    	break;
    case 38400:
       	*UART_IBRD=81;
    	*UART_FBRD=24;
    	break;
    case 57600:
        *UART_IBRD=54;
    	*UART_FBRD=16;
    	break;
    case 115200:
        *UART_IBRD=27;
    	*UART_FBRD=8;
    	break;
    }
    *UART_LCRH=0x70;
    *UART_CR=0x301;
}

void uart_write(char *buff, uint len) {
	uint i;
	for (i = 0; i < len; ++i) {
		while ((*UART_FR) & (1 << 5));
		*UART_DR = (uint)buff[i];
	}
	while (!(*UART_FR & FR_TXFE));
}

void uart_read(char *buff, uint len) {
	uint i;
	for (i = 0; i < len; ++i) {
		while ((*UART_FR) & (1 << 4));
		buff[i] = *UART_DR;
	}
}
