#include "gpio.h"

#define LEDPIN	47
#define DELAY	5000000


void delay(int n){
	while(n--){
		asm volatile("nop");
	}
}

void main(){
	gpio_open(LEDPIN, OUTPUT);

	while(1){
		gpio_write(LEDPIN, LOW);
		delay(DELAY);
		gpio_write(LEDPIN, HIGH);
		delay(DELAY);
	}
}

