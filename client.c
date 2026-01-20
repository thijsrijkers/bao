#include <errno.h>
#include <fcntl.h>
#include <netinet/tcp.h>
#include "client.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>


int accept_client_connection(int server_socket) {
    struct sockaddr_in client_addr = {0};

    socklen_t client_len = sizeof(client_addr);

    int client_connection = accept(server_socket, (struct sockaddr *)&client_addr, &client_len);

    if (client_connection < 0) {
        if (errno == EINTR) {
            return accept_client_connection(server_socket);
	    }

    	perror("accept");
	    return -1;
    }

    int flags = fcntl(client_connection, F_GETFL, 0);
    fcntl(client_connection, F_SETFL, flags | O_NONBLOCK);

    int flag = 1;
    setsockopt(client_connection, IPPROTO_TCP, TCP_NODELAY, &flag, sizeof(flag));

    return client_connection;
}
