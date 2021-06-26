#pragma once

#define PERIPH_BASE		0x20000000
#define GPIO_BASE		(PERIPH_BASE + 0x200000)
#define UART_BASE		(PERIPH_BASE + 0x201000)

#define GPIO_IN			0
#define GPIO_OUT		1
#define GPIO_FN0		4
#define GPIO_FN1		5
#define GPIO_FN2		6
#define GPIO_FN3		7
#define GPIO_FN4		3
#define GPIO_FN5		2

typedef unsigned int uint;

void uart_init();
void uart_read(char *buff, uint len);
void uart_write(char *buff, uint len);
void uart_flush();

void gpio_init(uint pin, uint mode);
void gpio_write(uint pin, uint val);
uint gpio_read(uint pin);
