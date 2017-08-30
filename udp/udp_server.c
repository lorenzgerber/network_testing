#define oops(s) {perror(s); exit(-1); }
#define BUFSIZE 200
/* Use your own settings */
#define PORT 2000
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
/* Util */
#include <stdio.h> /* perror */
#include <stdlib.h> /* exit */
#include <string.h> /* memset */
int main(int argc, char *argv[])
{
    struct sockaddr_in addr, from;
    int sock;
    unsigned int fromlen;
    char buf[BUFSIZE];
    if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
        oops("socket");
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(sock, (struct sockaddr *)&addr, sizeof (addr)) != 0)
        oops("bind");
    /* Server main loop; it here receivs "questions",
    processes them and sends the answer back */
    while (1) {
        fromlen = sizeof(from);
        recvfrom(sock, buf, BUFSIZE, 0, (struct sockaddr *)&from, &fromlen);
        /* process buf and create an answer also placed in buf
        and with new length n */
        sendto(sock, "FACK\n", 5, 0, (struct sockaddr *)&from, fromlen);
    }
}
