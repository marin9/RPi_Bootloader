#include <rpi.h>

#define UART_DR		((volatile uint*)(UART_BASE + 0x00))
#define UART_FR		((volatile uint*)(UART_BASE + 0x18))
#define UART_IBRD	((volatile uint*)(UART_BASE + 0x24))
#define UART_FBRD	((volatile uint*)(UART_BASE + 0x28))
#define UART_LCRH	((volatile uint*)(UART_BASE + 0x2C))
#define UART_CR		((volatile uint*)(UART_BASE + 0x30))
#define UART_ICR	((volatile uint*)(UART_BASE + 0x44))

#define CR_EN		(1 << 0)
#define CR_RXEN		(1 << 9)
#define CR_TXEN		(1 << 8)
#define FR_RXFE		(1 << 4)
#define FR_TXFF		(1 << 5)
#define FR_TXFE		(1 << 7)
#define LCRH_ENFIFO (1 << 4)
#define LCRH_WLEN8	(3 << 5)

#define UART_TX		14
#define UART_RX		15
#define UART_BAUD	115200


void uart_init() {
	gpio_init(UART_TX, GPIO_FN0);
	gpio_init(UART_RX, GPIO_FN0);

	*UART_CR = 0;
    *UART_ICR = 0x7FF;
	// baud_rate = 115200
	*UART_IBRD = 27;
    *UART_FBRD = 8;
    *UART_LCRH = LCRH_WLEN8 | LCRH_ENFIFO;
	*UART_CR = CR_EN | CR_RXEN | CR_TXEN;
}

void uart_write(char *buff, uint len) {
	uint i;
	for (i = 0; i < len; ++i) {
		while (*UART_FR & FR_TXFF);
		*UART_DR = buff[i];
	}
}

void uart_read(char *buff, uint len) {
	uint i;
	for (i = 0; i < len; ++i) {
		while (*UART_FR & FR_RXFE);
		buff[i] = *UART_DR;
	}
}

void uart_flush() {
	while(!(*UART_FR & FR_TXFE));
}
