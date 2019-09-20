#include "gpio.h"

#define LEDPIN	47
#define DELAY	5000000


void delay(int n){
	while(n--){
		asm volatile("nop");
	}
}

void main(){
	gpio_mode(LEDPIN, OUTPUT);

	while(1){
		gpio_set(LEDPIN, HIGH);
		delay(DELAY);
		gpio_set(LEDPIN, LOW);
		delay(DELAY);
	}
}

