#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int skt, port, len, k;
    struct sockaddr_in server, srvres;
    char buf[1024], res[1024];

    if (argc == 2) {
        port = atoi(argv[1]);
    } else {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        return 1;
    }

    skt = socket(AF_INET, SOCK_DGRAM, 0);
    
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);
    
    len = sizeof(srvres);
    printf("> ");
    scanf("%s", buf);
    if(sendto(skt, buf, strlen(buf)+1, 0, (struct sockaddr *) &server, sizeof(server)) < 0) {
        perror("While Sending");
    } else {
        if(recvfrom(skt, res, sizeof(res), 0, (struct sockaddr *) &srvres, &len) < 0) {
            perror("While Receiving Response");
        } else {
            printf("Response: %s\n", res);
        }
    }
    close(skt);

    return 0;
}
