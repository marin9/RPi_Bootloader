#include <rpi.h>

#define GPFSEL0     ((volatile uint*)(GPIO_BASE + 0x00))
#define GPFSEL1     ((volatile uint*)(GPIO_BASE + 0x04))
#define GPFSEL2     ((volatile uint*)(GPIO_BASE + 0x08))
#define GPFSEL3     ((volatile uint*)(GPIO_BASE + 0x0C))
#define GPFSEL4     ((volatile uint*)(GPIO_BASE + 0x10))
#define GPFSEL5     ((volatile uint*)(GPIO_BASE + 0x14))
#define GPSET0      ((volatile uint*)(GPIO_BASE + 0x1C))
#define GPSET1      ((volatile uint*)(GPIO_BASE + 0x20))
#define GPCLR0      ((volatile uint*)(GPIO_BASE + 0x28))
#define GPCLR1      ((volatile uint*)(GPIO_BASE + 0x2C))
#define GPLEV0      ((volatile uint*)(GPIO_BASE + 0x34))
#define GPLEV1      ((volatile uint*)(GPIO_BASE + 0x38))


void gpio_init(uint pin, uint mode) {
    if (pin < 10)      *GPFSEL0 &= ~(7 << ((pin - 0) * 3));
    else if (pin < 20) *GPFSEL1 &= ~(7 << ((pin - 10) * 3));
    else if (pin < 30) *GPFSEL2 &= ~(7 << ((pin - 20) * 3));
    else if (pin < 40) *GPFSEL3 &= ~(7 << ((pin - 30) * 3));
    else if (pin < 50) *GPFSEL4 &= ~(7 << ((pin - 40) * 3));
    else if (pin < 60) *GPFSEL5 &= ~(7 << ((pin - 50) * 3));

    if (pin < 10)      *GPFSEL0 |= mode << ((pin - 0) * 3);
    else if (pin < 20) *GPFSEL1 |= mode << ((pin - 10) * 3);
    else if (pin < 30) *GPFSEL2 |= mode << ((pin - 20) * 3);
    else if (pin < 40) *GPFSEL3 |= mode << ((pin - 30) * 3);
    else if (pin < 50) *GPFSEL4 |= mode << ((pin - 40) * 3);
    else if (pin < 60) *GPFSEL5 |= mode << ((pin - 50) * 3);
}

void gpio_write(uint pin, uint val) {
    if (pin >= 32) {
        if (val)
            *GPSET1 =1 << (pin - 32);
        else
            *GPCLR1 =1 << (pin - 32);
    } else {
        if (val)
            *GPSET0 = 1 << pin;
        else
            *GPCLR0 = 1 << pin;
    }
}

uint gpio_read(uint pin) {
    if (pin >= 32)
        return ((*GPLEV1) >> (pin - 32)) & 1;
    else
        return ((*GPLEV0) >> pin) & 1;
}
