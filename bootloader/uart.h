#pragma once

void uart_init();
int uart_send(void *buf, int len);
int uart_recv(void *buf, int len);
