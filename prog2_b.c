#include <stdio.h>
#include <netdb.h>

int main() {
    struct hostent *hd;
    hd = gethostbyaddr("10.10.151.12", 4, AF_INET);
    printf("The host name resolved for 10.10.151.12: %s\n", hd->h_name);
    return 0;
}
