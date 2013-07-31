#include <stdio.h>
#include <netdb.h>

int main() {
    int i;
    struct hostent *hd;
    struct in_addr **addr_list;
    char **aliases;
    hd = gethostbyname("www.google.com");
    addr_list = (struct in_addr **) hd->h_addr_list;
    aliases = hd->h_aliases;
    printf("DNS lookup for www.google.com\n\n");
    printf("Resolved IP Addresses:\n");
    for (i=0; addr_list[i]; i++) {
        printf("%u: %s\n", i, inet_ntoa(*addr_list[i]));
    }
    printf("No. of IPs resolved: %d\n", i);
    printf("\nResolved Aliases:\n");
    for (i=0; aliases[i]; i++) {
        printf("%u: %s\n", i, aliases[i]);
    }
    printf("No. of Aliases resolved: %d\n", i);
    return 0;
}
