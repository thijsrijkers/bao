#ifndef SERVER_H
#define SERVER_H
#include <stdint.h>

int create_server_socket(uint16_t port, int connection_amount);

#endif