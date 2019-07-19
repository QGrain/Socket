#include <stdio.h>
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdint.h>

#include "socketHeaders.h"
#define ETH_LEN 6

int main()
{
    WSADATA wsadata;
    int status;

    status = WSAStartup(MAKEWORD(2, 2), &wsadata);
    if(status != 0) {
        fprintf(stderr, "WSAStartup error with GetLastError code: %d\n", WSAGetLastError());
    }

    SOCKET sniffer_socket = socket(AF_INET, SOCK_RAW, IPPROTO_IP);
    if(sniffer_socket == SOCKET_ERROR) {
        fprintf(stderr, "Failed to create socket!\n");
        goto Exit;
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

    u_long sioarg = 1;
    DWORD dwValue = 0;
    status = WSAIoctl(sniffer_socket, SIO_RCVALL, &sioarg, sizeof(sioarg), NULL, 0, &dwValue, NULL, NULL);
    if(status == SOCKET_ERROR) {
        fprintf(stderr, "Failed in WSAIoctl(), with GetLastError code: %d\n", WSAGetLastError());
        goto Exit;
    }

    char buf[65535];
    int len = 0;
    int count = 0;
    listen(sniffer_socket, 5);
    do {
        len = recv(sniffer_socket, buf, sizeof(buf), 0);
        if(len > 0) {
            ++count;
            fprintf(stderr, "recv %d packet!\n", count);
        }
    }while(len > 0);

Exit:
    WSACleanup();
    return 0;
}