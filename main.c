#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "server.h"
#include "client.h"

int main(int argc, char *argv[]) {
    printf("Load balancer starting\n");

    int server_socket = create_server_socket(8080, 5);
    if (server_socket < 0){
	    return -1;
    }
    
    printf("Server socket listing on port: 8080\n");

    while (1) {
    	int client_connection = accept_client_connection(server_socket);
    	if (client_connection < 0) {
            continue;
    	}

    	printf("Accepted new client: fd=%d\n", client_connection);

    	close(client_connection);
    }

    printf("Load balancer closing.\n");
    return 0;
}
