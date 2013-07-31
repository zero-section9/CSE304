#include <stdio.h>
#include <netdb.h>

void lookupIP() {
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

void lookupHost(char *addr) {
    struct hostent *hd;
    hd = gethostbyaddr(addr, 4, AF_INET);
    printf("%s\n", hd->h_name);
}

void lookup(char *in) {
   if ('0' <= in[1] && in[1] <= '9') {
       return lookupHost(in);
   } else {
       return lookupIP(in);
   }
}

int main(int argc, char **argv) {
    char in[50];
    if (argc == 1) {
        while (1) {
            printf("\n> ");
            scanf("%s", in);
            if (stricmp(in, "exit") == 0) {
                return 0;
            }
        }
    } else if (argc == 2) {
        lookup(argv[1]);
    } else {
        fprintf(stderr, "Usage: %s [Hostname | IP Address]");
        return 1;
    }
    return 0;
}
