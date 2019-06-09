#include <stdio.h>
//#include <winsock2.h>
#include <Ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")
int main()
{
    WSADATA wsaData;
    SOCKET Client;
    SOCKADDR_IN ServerAddr;
    int port = 10472;
    char recver[100];

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        fprintf(stderr, "WSAStartup failed\n");
        return 1;
    }

    Client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    ServerAddr.sin_family = AF_INET;
    ServerAddr.sin_port = htons(port);
    ServerAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
    //inet_pton(AF_INET, "127.0.0.1", (void *)&ServerAddr.sin_addr.S_un.S_addr);
    
    //fprintf(stderr, "sin_addr.S_un.S_addr: %d\n", ServerAddr.sin_addr.S_un.S_addr);
    //fprintf(stderr, "addr test %d\naddr test %d\naddr test %d\n", inet_addr("127.0.0.2"), inet_addr("127.0.1.1"), inet_addr("128.0.0.1"));

    fprintf(stderr, "\nconnect() start\n");
    connect(Client, (SOCKADDR *)&ServerAddr, sizeof(ServerAddr));
    fprintf(stderr, "connect() success!\n");

    recv(Client, recver, sizeof(recver), 0);
    fprintf(stderr, "Receive from server: %s\nsize of recver:%d", recver, sizeof(recver));

    closesocket(Client);
    WSACleanup();

    return 0;
}