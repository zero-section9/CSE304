#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    char fn[150], buf[100];
    socklen_t len;
    int port, k, sock_desc, temp_sock_desc;
    struct sockaddr_in client, server;

    memset(&server, 0, sizeof(server));
    if (argc == 2) {
        port = atoi(argv[1]);
    } else {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        return 1;
    }
    
    printf("Initializing Server... ");
    sock_desc = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = port;

    printf("done.\nBinding Server... ");
    k = bind(sock_desc, (struct sockaddr *) &server, sizeof(server));
    if (k < 0) {
         printf("\n");
         perror("bind");
         return k;
    }
    printf("done.\nStart Listening at port %d... ", port);
    k = listen(sock_desc, 20);
    if (k < 0) {
         printf("\n");
         perror("listen");
         return k;
    }
    printf("done.\n");
    
    len = sizeof(client);
    while (1) {
        memset(&client, 0 , sizeof(client));
        temp_sock_desc = accept(sock_desc, (struct sockaddr *) &client, &len);
        recv(temp_sock_desc, fn, sizeof(fn));
        printf("Requested File Name: %s\n");
        printf("Sending File");
        send(temp_sock_desc, , strlen()+1, 0);
        printf("done.\n");
        close(temp_sock_desc);
    }
    close(sock_desc);

    return 0;
}
