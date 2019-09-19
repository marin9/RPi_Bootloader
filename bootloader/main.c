#include "uart.h"
#include "gpio.h"
#include "string.h"


#define ACT_LED		47
#define PACK_LEN 	32
#define PROG_ADDR	0x10000

#define CMD_TEST	0
#define CMD_EXE		1


void send_msg(int code, char *s){
	char buf[PACK_LEN];

	buf[0]=code;
	strcpy(buf+1, s);
	uart_send(buf, PACK_LEN);
}

void run_prog(int addr){
	addr=addr;
	asm volatile("bx r0");
}


void main(){
	char req[PACK_LEN];

	uart_init();
	gpio_mode(ACT_LED, OUTPUT);
	gpio_set(ACT_LED, LOW);


	while(1){
		uart_recv(req, PACK_LEN);
		gpio_set(ACT_LED, HIGH);

		switch(req[0]){
		case CMD_TEST:
			send_msg(0, "ACK");
			break;

		case CMD_EXE:
			send_msg(0, "ACK");
			uart_recv((char*)PROG_ADDR, atoi(req+1));
			send_msg(0, "FIN");

			gpio_set(ACT_LED, LOW);
			run_prog(PROG_ADDR);
			break;

		default:
			send_msg(0xFF, "Unsupported operation.");
			break;
		}
		gpio_set(ACT_LED, LOW);
	}
}
