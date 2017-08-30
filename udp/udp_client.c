#define _XOPEN_SOURCE 600
#define BUFSIZE 200
/* Use your own settings */
#define HOSTNAME "127.0.0.1"
#define HOSTPORT "2000"
#define oops(s) {perror(s); exit(-1); }
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
/* Util */
#include <stdio.h> /* perror */
#include <stdlib.h> /* exit */
#include <string.h> /* memset */
int main(int argc, char *argv[])
{
    struct sockaddr_in addr;
    int sock, status;
    char buf[BUFSIZE];
    struct addrinfo *res, hints;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_protocol = 0;
    hints.ai_flags = AI_ADDRCONFIG;
    if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
        oops("socket")
    /* Build the network address of this client */
    addr.sin_family = AF_INET;
    addr.sin_port = htons(0);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(sock, (struct sockaddr *)&addr, sizeof (addr)) != 0)
        oops("bind");
    /* Build the network address of server */
    status = getaddrinfo(HOSTNAME, HOSTPORT, &hints, &res);
    switch (status) {
        /* Check errnos from getaddrinfo */
        case 0: // Success
            break;
        default:
            oops("getaddrinfo");
    }
    /* Create a message to the server */
    sprintf(buf, "Some data\n");
    /* Send it to the server */
    sendto(sock, buf, strlen(buf), 0, (struct sockaddr *)res->ai_addr, res->ai_addrlen);
    /* Receive the answer */
    memset(buf, 0, BUFSIZE);
    recvfrom(sock, buf, BUFSIZE, 0, (struct sockaddr *)res->ai_addr, &res->ai_addrlen);
    /* process the answer */
    printf("%s", buf);
    /* free getaddrinfo struct */
    free(res);
}
