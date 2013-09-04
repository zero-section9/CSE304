#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int skt, port, len, k;
    struct sockaddr_in address, client;
    char buf[1024];
    const char success_res[] = "Message Received Successfully.";
    const char err_res[] = "Transmision Error!";

    if (argc == 2) {
        port = atoi(argv[1]);
    } else {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        return 1;
    }

    skt = socket(AF_INET, SOCK_DGRAM, 0);
    
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(port);

    if (bind(skt, (struct sockaddr *) &address, sizeof(address)) < 0) {
        perror("While binding");
        return 0;
    }
    
    len = sizeof(client);
    memset(&client, 0 , sizeof(client));
    if(recvfrom(skt, buf, sizeof(buf), 0, (struct sockaddr *) &client, &len) < 0) {
        perror("While Receiving");
        if(sendto(skt, err_res, sizeof(err_res), 0, (struct sockaddr *) &client, len) < 0) {
            perror("While Sending Error Respose");
        }
    } else {
        printf("Msg: %s\n", buf);
        if(sendto(skt, success_res, sizeof(success_res), 0, (struct sockaddr *) &client, len) < 0) {
            perror("While Sending Success Respose");
        }
    }
    close(skt);

    return 0;
}
