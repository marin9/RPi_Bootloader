#pragma once

void serial_open();
void serial_close();
void serial_send(char *buff, int len);
void serial_recv(char *buff, int len);
