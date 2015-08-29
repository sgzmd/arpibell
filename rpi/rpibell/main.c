/*
 * Original code from http://www.ccplusplus.com/2011/09/udp-client-example-in-c.html
 * Modifications (C) Roman Kirillov 2015
 */

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/errno.h>
#include <stdlib.h>
#include <mach/boolean.h>
#include "mkaddr.h"


static void displayError(const char *on_what) {
    fputs(strerror(errno), stderr);
    fputs(": ", stderr);
    fputs(on_what, stderr);
    fputc('\n', stderr);
    exit(1);
}


int main(int argc, char **argv) {
    int bytes_recvd;
    socklen_t addr_length;
    struct sockaddr_in addr;  /* AF_INET */
    int len_inet;            /* length */
    int udp_socket;                   /* Socket */
    char dgram[512];         /* Recv buffer */
    static int so_reuseaddr = TRUE;
    static char *bc_addr = "127.255.255.2:9097";

    /*
     * Use a server address from the command
     * line, if one has been provided.
     * Otherwise, this program will default
     * to using the arbitrary address
     * 127.0.0.:
     */
    if (argc > 1)
        /* Broadcast address: */
        bc_addr = argv[1];

    /*
     * Create a UDP socket to use:
     */
    udp_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (udp_socket == -1)
        displayError("socket()");

    /*
     * Form the broadcast address:
     */
    len_inet = sizeof addr;

    bytes_recvd = mkaddr(&addr,
                         &len_inet,
                         bc_addr,
                         "udp");

    if (bytes_recvd == -1)
        displayError("Bad broadcast address");

    /*
     * Allow multiple listeners on the
     * broadcast address:
     */
    bytes_recvd = setsockopt(udp_socket,
                             SOL_SOCKET,
                             SO_REUSEADDR,
                             &so_reuseaddr,
                             sizeof so_reuseaddr);

    if (bytes_recvd == -1)
        displayError("setsockopt(SO_REUSEADDR)");

    /*
     * Bind our socket to the broadcast address:
     */
    bytes_recvd = bind(udp_socket,
                       (struct sockaddr *) &addr,
                       len_inet);

    if (bytes_recvd == -1)
        displayError("bind(2)");

    for (;;) {
        /*
         * Wait for a broadcast message:
         */
        bytes_recvd = recvfrom(udp_socket,      /* Socket */
                               dgram,           /* Receiving buffer */
                               sizeof dgram,    /* Max rcv buf size */
                               0,               /* Flags: no options */
                               (struct sockaddr *) &addr, /* Addr */
                               &addr_length);   /* Addr len, in & out */

        if (bytes_recvd < 0)
            displayError("recvfrom(2)"); /* else err */

        fwrite(dgram, bytes_recvd, 1, stdout);
        putchar('\n');

        fflush(stdout);
    }
}