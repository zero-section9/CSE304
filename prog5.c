#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    char buf[100];
    socklen_t len;
    int k, sock_desc, temp_sock_desc;
    struct sockaddr_in client, server;
    memset(&client, 0, sizeof(client));
    memset(&server, 0, sizeof(server));
    printf("Initializing Server... ");
    sock_desc = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = 37777;
    printf("done.\nBinding Server... ");
    k = bind(sock_desc, (struct sockaddr *) &server, sizeof(server));
    if (k < 0) {
         perror(errno);
         return k;
    }
    printf("done.\nStart Listening... ");
    k = listen(sock_desc, 20);
    if (k < 0) {
         perror(errno);
         return k;
    }
    printf("done.\n");
    len = sizeof(client);
    
    int i = 0;
    while (1) {
        temp_sock_desc = accept(sock_desc, (struct sockaddr *) &client, &len);
        printf("Connection %d:\n", i);
        while (1) {
            k = recv(temp_sock_desc, buf, 100, 0);
            if (k > 0) {
                printf("%s", buf);
            }
        }
    }
    return 0;
}
