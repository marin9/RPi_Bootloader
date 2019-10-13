#include "uart.h"
#include "gpio.h"
#include "string.h"

#define ACT_LED		47
#define PACK_LEN 	32
#define PROG_ADDR	0x10000

#define CMD_TEST	0
#define CMD_EXE		1


void run_prog(int addr){
	addr=addr;
	asm volatile("bx r0");
}


void main(){
	int size;
	char req[PACK_LEN];

	uart_init();
	gpio_mode(ACT_LED, OUTPUT);
	gpio_set(ACT_LED, LOW);

	while(1){
		uart_recv(req, PACK_LEN);
		gpio_set(ACT_LED, HIGH);

		switch(req[0]){
		case CMD_TEST:
			strcpy(req, "Ready");
			uart_send(req, PACK_LEN);
			break;
		case CMD_EXE:
			size=atoi(req+1);
			strcpy(req, "Ready");
			uart_send(req, PACK_LEN);

			uart_recv((char*)PROG_ADDR, size);
		
			strcpy(req, "Data received.");
			uart_send(req, PACK_LEN);

			gpio_set(ACT_LED, LOW);
			run_prog(PROG_ADDR);
			break;

		default:
			strcpy(req, "Unsupported operation.");
			uart_send(req, PACK_LEN);
			break;
		}
		gpio_set(ACT_LED, LOW);
	}
}
