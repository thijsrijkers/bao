#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "server.h"

int create_server_socket(uint16_t port, int connection_amount)
{
    int server_socket;

    // Make Socket for IPV4, set socket to stream_oriented and set default protocol
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("socket");
	    return -1;
    }

    struct sockaddr_in address;
    memset(&address, 0, sizeof(address));

    address.sin_family = AF_INET; // Sets IPV4
    address.sin_addr.s_addr = INADDR_ANY; // Sets acceptance of external connections
    address.sin_port = htons(port); // Sets given port

    if (bind(server_socket, (struct sockaddr*)&address, sizeof(address)) < 0) {
	    perror("bind");
	    close(server_socket);
	    return -1;
    }

    // Setup socket to listen and allow 3 pending connections maxs
    if (listen(server_socket, connection_amount) < 0) { 
    	perror("listen");
    	close(server_socket);
    	return -1;
    }

    return server_socket;
}

