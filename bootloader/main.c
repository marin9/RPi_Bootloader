#include "rpi.h"

#define READY_LED	21
#define BUSY_LED	26
#define ACT_LED		47

#define PACK_LEN 	32
#define PROG_ADDR	0x10000

#define CMD_TEST	0
#define CMD_EXE		1


char *strcpy(char *dest, char *src) {
	int i = 0;
	while (src[i]) {
		dest[i] = src[i];
		++i;
	}
	dest[i] = 0;
	return dest;
}

int atoi(char *str) {
	int i = 0;
	int res = 0;

    while (str[i]) {
        res = res * 10 + str[i] - '0';
		++i;
    }
    return res;
}


void run_prog(int addr) {
	addr = addr;
	asm volatile("bx r0");
}


void setup() {
	int size;
	char req[PACK_LEN];

	uart_init(115200);
	gpio_mode(READY_LED, GPIO_OUT);
	gpio_mode(BUSY_LED, GPIO_OUT);
	gpio_mode(ACT_LED, GPIO_OUT);

	while (1) {
		gpio_write(READY_LED, 1);
		gpio_write(BUSY_LED, 0);
		gpio_write(ACT_LED, 0);

		uart_read(req, PACK_LEN);
		gpio_write(READY_LED, 0);
		gpio_write(BUSY_LED, 1);
		gpio_write(ACT_LED, 1);

		switch (req[0]) {
		case CMD_TEST:
			strcpy(req, "Ready");
			uart_write(req, PACK_LEN);
			break;

		case CMD_EXE:
			size = atoi(req + 1);
			strcpy(req, "Ready");
			uart_write(req, PACK_LEN);

			uart_read((char*)PROG_ADDR, size);

			strcpy(req, "Data received.");
			uart_write(req, PACK_LEN);

			gpio_write(READY_LED, 0);
			gpio_write(BUSY_LED, 0);
			gpio_write(ACT_LED, 0);
			run_prog(PROG_ADDR);
			break;

		default:
			strcpy(req, "Unsupported operation.");
			uart_write(req, PACK_LEN);
			break;
		}
	}
}
