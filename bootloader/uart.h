#pragma once

void uart_init();
void uart_send(void *buf, int len);
void uart_recv(void *buf, int len);
