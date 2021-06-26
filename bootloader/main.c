#include <rpi.h>

#define LED			47

#define PACK_LEN 	32
#define PROG_ADDR	0x8000

#define CMD_TEST	0
#define CMD_LOAD	1


void strcpy(char *dest, char *src) {
	int i = 0;
	while (src[i]) {
		dest[i] = src[i];
		++i;
	}
	dest[i] = 0;
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

void run_prog(uint addr) {
	void (*func)();
	func = (void*)addr;
	func();
}


void main() {
	int size;
	char req[PACK_LEN];

	uart_init();
	gpio_init(LED, GPIO_OUT);

	while (1) {
		gpio_write(LED, 0);
		uart_read(req, PACK_LEN);

		gpio_write(LED, 1);

		switch (req[0]) {
		case CMD_TEST:
			strcpy(req, "Bootloader v2.0 OK");
			uart_write(req, PACK_LEN);
			uart_flush();
			break;

		case CMD_LOAD:
			size = atoi(req + 1);
			uart_read((char*)PROG_ADDR, size);

			strcpy(req, "Done.");
			uart_write(req, PACK_LEN);
			uart_flush();

			gpio_write(LED, 0);
			run_prog(PROG_ADDR);
			break;

		default:
			strcpy(req, "Unsupported operation.");
			uart_write(req, PACK_LEN);
			uart_flush();
			break;
		}
	}
}
