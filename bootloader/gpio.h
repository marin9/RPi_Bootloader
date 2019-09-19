#pragma once

#define INPUT	0
#define OUTPUT	1
#define LOW 	0
#define HIGH 	1

void gpio_mode(int pin, int mode);
void gpio_set(int pin, int stat);
int gpio_get(int pin);

