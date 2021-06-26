#include <gpio.h>

#define LED		47
#define DELAY	2000000


void delay(int n) {
	while (n--)
		asm volatile("nop");
}

void main() {
	gpio_init(LED, GPIO_OUT);

	while (1) {
		gpio_write(LED, 0);
		delay(DELAY);
		gpio_write(LED, 1);
		delay(DELAY);
	}
}
