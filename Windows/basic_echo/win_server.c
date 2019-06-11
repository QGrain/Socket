#include <stdio.h>
#include <winsock2.h>
#include <windows.h>

#pragma comment(lib, "ws2_32.lib") //GCC will ignore this statement???

int main()
{
    WSADATA wsaData;
    SOCKET ListeningSocket, newConnection;
    SOCKADDR_IN ServerAddr, ClientAddr;
    const int port = 10472;
    const char hello[] = "Hello, your connection is success.\n";
    if (WSAStartup (MAKEWORD(2, 2), &wsaData) != 0) {
        fprintf(stderr, "WSAStartup Failed!\n");
        return 1;
    }

    //Create a socket
    ListeningSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (ListeningSocket >= 0) {
        fprintf(stderr, "socket create successfully!\n");
    }
    else {
        fprintf(stderr, "socket create failed!\n");
        return 1;
    }
    ServerAddr.sin_family = AF_INET;
    ServerAddr.sin_port = htons(port);
    ServerAddr.sin_addr.S_un.S_addr = INADDR_ANY;

    //bind address
    bind(ListeningSocket, (SOCKADDR*)&ServerAddr, sizeof(ServerAddr));
    //fprintf(stderr, "bind finished with these info:\n");
    //fprintf(stderr, "sin_family: %d\nsin_port:%d\nsin_addr.S_un.S_addr:%d\nsin_zero:%x\n", ServerAddr.sin_family, ntohs(ServerAddr.sin_port), ServerAddr.sin_addr.S_un.S_addr, ServerAddr.sin_zero);

    //listen for client
    fprintf(stderr, "\nStart to listen\n");
    listen(ListeningSocket, 5);
    fprintf(stderr, "listen finished\n");

    //accept the client
    int ClientAddrLen;
    newConnection = accept(ListeningSocket, (SOCKADDR*)&ClientAddr, &ClientAddrLen);
    fprintf(stderr, "\naccept() success! ClientAddrLen is %d\n", ClientAddrLen);

    send(newConnection, hello, sizeof(hello), 0);
    fprintf(stderr, "send() successfully with sizeof %d\n", sizeof(hello));

    closesocket(newConnection);
    closesocket(ListeningSocket);
    fprintf(stderr, "\nsockets close successfully\n");

    WSACleanup();

    return 0;
}