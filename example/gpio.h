#pragma once

#define INPUT	0
#define OUTPUT	1
#define LOW 	0
#define HIGH 	1

void gpio_open(int pin, int mode);
void gpio_write(int pin, int stat);
int gpio_read(int pin);
