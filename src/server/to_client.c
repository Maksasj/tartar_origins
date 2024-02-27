#include "to_client.h"

int handle_client(void *ptr) {
    Connection* connection = (Connection*) ptr;

    char buffer[1024];
    memset(&buffer,0,sizeof(buffer));

    while(1) {
        int s_len = recv(connection->c_socket, buffer,sizeof(buffer),0);
        int r_len = send(connection->c_socket,buffer,s_len,0);

        printf("IP: %s Sent: %d Received: %d\n", inet_ntoa(connection->clientaddr.sin_addr), s_len, r_len);
    }

    close(connection->c_socket);

    return 0;
}
