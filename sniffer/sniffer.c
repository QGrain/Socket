#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdint.h>

#include "socketHeaders.h"
#include "api.h"


int main()
{
    WSADATA wsadata;
    int status;

    status = WSAStartup(MAKEWORD(2, 2), &wsadata);
    if(status != 0) {
        fprintf(stderr, "WSAStartup error with GetLastError code: %d\n", WSAGetLastError());
    }

    fprintf(stderr, "Sniffer start!\n");

    //Create raw socket
    SOCKET sniffer_socket = socket(AF_INET, SOCK_RAW, IPPROTO_IP);
    if(sniffer_socket == SOCKET_ERROR) {
        fprintf(stderr, "Failed to create socket!\n");
        goto Exit;
    }
    else {
        fprintf(stderr, "Socket created successfully!\n");
    }

    SOCKADDR_IN sniffer_addr;
    sniffer_addr.sin_addr.S_un.S_addr = inet_addr("192.168.9.189");
    sniffer_addr.sin_family = AF_INET;
    sniffer_addr.sin_port = htons(8888);

    status = bind(sniffer_socket, (struct sockaddr *)&sniffer_addr, sizeof(sniffer_addr));
    if(status == SOCKET_ERROR) {
        fprintf(stderr, "Failed to bind, with GetLastError code: %d\n", WSAGetLastError());
        goto Exit;
    }

    //Set the Socket as receiving all the packets flowing through this IP-binded interface
    u_long sioarg = 1;
    DWORD dwValue = 0;
    status = WSAIoctl(sniffer_socket, SIO_RCVALL, &sioarg, sizeof(sioarg), NULL, 0, &dwValue, NULL, NULL);
    if(status == SOCKET_ERROR) {
        fprintf(stderr, "Failed in WSAIoctl(), with GetLastError code: %d\n", WSAGetLastError());
        goto Exit;
    }


    //Listen with 5 in queue at a time
    listen(sniffer_socket, 5);
    int pkt_len = 0;
    int pkt_count = 0;
    char recv_buf[MAX_TRANS_UNIT];
    memset(recv_buf, 0, MAX_TRANS_UNIT);
    while(1) {
        pkt_len = recv(sniffer_socket, recv_buf, sizeof(recv_buf), 0);
        if(pkt_len > 0) {
            ++pkt_count;
            fprintf(stderr, "recv %d packet, with size %d bytes!\n", pkt_count, pkt_len);
            //pkt_dump(recv_buf, strlen(recv_buf));
            memset(recv_buf, 0, MAX_TRANS_UNIT);
        }
        else if(pkt_len == 0) {
            fprintf(stderr, "receive length = 0, exit recv loop!\n");
            break;
        }
    }

//recycle the resources
Exit:
    if(sniffer_socket != SOCKET_ERROR) {
        closesocket(sniffer_socket);
    }
    WSACleanup();
    fprintf(stderr, "Sniffer stop!\n");
    return 0;
}