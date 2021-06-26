#pragma once

#define GPIO_IN	    0
#define GPIO_OUT	1

void gpio_init(int pin, int mode);
void gpio_write(int pin, int stat);
int gpio_read(int pin);
