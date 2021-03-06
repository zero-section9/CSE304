#include <sys/socket.h> 
#include <netinet/in.h> 
#include <stdio.h> 
#include <string.h> 
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    char buf[100];
    struct sockaddr_in client;
    int port, sock_desc, k;

    if (argc == 2) {
        port = atoi(argv[1]);
    } else {
        fprintf(stderr, "Usage: %s <port number>\n", argv[0]);
        return 1;
    }

    sock_desc = socket(AF_INET, SOCK_STREAM, 0);
    memset(&client, 0, sizeof(client));
    client.sin_family = AF_INET;
    client.sin_addr.s_addr = INADDR_ANY;
    client.sin_port = port;

    printf("Establishing Connection... ");
    k = connect(sock_desc, (struct sockaddr*)&client, sizeof(client));
    if (k < 0) {
        printf("\n");
        perror("connect");
        return k;
    }
    printf("tested successfully.\n");
    close(sock_desc);

    return 0;
}
