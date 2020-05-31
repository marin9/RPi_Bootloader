#include "gpio.h"

#define LED0	47
#define LED1	21
#define DELAY	2000000


void delay(int n) {
	while (n--)
		asm volatile("nop");
}

void main() {
	gpio_open(LED0, GPIO_OUT);
	gpio_open(LED1, GPIO_OUT);

	while (1) {
		gpio_write(LED0, 0);
		gpio_write(LED1, 0);
		delay(DELAY);
		gpio_write(LED0, 1);
		gpio_write(LED1, 1);
		delay(DELAY);
	}
}
