#pragma once

void serial_open();
void serial_close();
void serial_send(char *buff, uint len);
void serial_recv(char *buff, uint len);
