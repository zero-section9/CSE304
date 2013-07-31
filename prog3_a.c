#include <netdb.h>
#include <stdio.h>

int main(int argc, char **argv) {
    struct servent *serv;
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <network sevice> <protocol>\n", argv[0]);
        return 1;
    }
    serv = getservbyname(argv[1], argv[2]);
    printf("The %s service over %s protocol listens on port %d.\n", argv[1], argv[2], ntohs(serv->s_port));
    return 0;
}
