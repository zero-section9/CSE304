#include <netdb.h>
#include <stdio.h>

int main(int argc, char **argv) {
    struct servent *serv;
    int port;
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <port> <protocol>\n", argv[0]);
        return 1;
    }
    sscanf(argv[1], "%d", &port);
    serv = getservbyport(htons(port), argv[2]);
    printf("The port %d under %s protocol hosts %s service.\n", port, argv[2], serv->s_name);
    return 0;
}
