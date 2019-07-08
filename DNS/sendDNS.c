#include <stdio.h>
#include <windows.h>
#include <winsock2.h>
#include "dnsHeader.h"

#pragma comment(lib, "ws2_32.lib")

BOOLEAN sendDNS(SOCKET sendSocket, const char *DomainName, const char *dnsServer);
BOOLEAN verifyDomainName(const char *DomainName);
int lastIsDot(const char *DomainName);
void Domain2QueryName(const char *DomainName, char *QueryName);



int main()
{   
    BOOLEAN status = FALSE;
    char *DomainName = "baidu.com";
    char *dnsServer = "192.168.11.101";

    WSADATA wsaData;
    SOCKET sendSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if(sendSocket < 0) {
        fprintf(stderr, "Create Socket failed, pSocket is %d\n", sendSocket);
        goto Exit;
    }

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        fprintf(stderr, "WSAStartup failed\n");
        goto Exit;
    }

    status = sendDNS(sendSocket, DomainName, dnsServer);
    if(status == FALSE) {
        fprintf(stderr, "main() return, send failed!\n");
        goto Exit;
    }


Exit:
    closesocket(sendSocket);
    WSACleanup();
    return 0;
}

BOOLEAN sendDNS(SOCKET sendSocket, const char *DomainName, const char *dnsServer)	//DNS server is 202.114.0.131 for default
{
    BOOLEAN sendStatus = FALSE;
    BOOLEAN dnIsValid = verifyDomainName(DomainName);

    if(dnsServer == NULL || dnIsValid == FALSE) {
        fprintf(stderr, "dnsServer or dnsName not valid\n");
        goto Exit;
    }

    int extraLen = 1 + lastIsDot(DomainName);
    unsigned int DomainNameLen = strlen(DomainName);
    unsigned int QueryNameLen = DomainNameLen + extraLen;

    char *QueryName = (char *)malloc(QueryNameLen);
    Domain2QueryName(DomainName, QueryName);

    DNSHeader *pPACKHeader = (DNSHeader *)malloc(sizeof(DNSHeader *) + QueryNameLen + 4);
    if(pPACKHeader == NULL) {
        fprintf(stderr, "Create pPACKHeader failed!\n");
        goto Exit;
    }

    
    memset(pPACKHeader, 0, sizeof(DNSHeader *) + QueryNameLen + 4);

    pPACKHeader->Trans_ID = htons(0x0001);
    pPACKHeader->RD = 0b1;
    pPACKHeader->Qestions = htons(0x0001);

    BYTE *pTEXT = (BYTE *)pPACKHeader + sizeof(DNSHeader);
    memcpy(pTEXT, QueryName, QueryNameLen);

    unsigned short *queryType = (unsigned short *)(pPACKHeader + QueryNameLen);
    *queryType = htons(0x0001);     //TYPE A, query return ipv4 address

    ++queryType;
    *queryType = htons(0x0001);     //CLASS IN, for Internet.


    //Send Pack:
    SOCKADDR_IN dnsServAddr;
    dnsServAddr.sin_family = AF_INET;
    dnsServAddr.sin_port = htons(53);
    dnsServAddr.sin_addr.S_un.S_addr = inet_addr(dnsServer);

    fprintf(stderr, "Ready to send!\n");

int ret = sendto(sendSocket, (char *)pPACKHeader, sizeof(DNSHeader *) + QueryNameLen + 4, 0, (SOCKADDR *)&dnsServAddr, sizeof(dnsServAddr));
    if(ret == SOCKET_ERROR) {
        fprintf(stderr, "GetLastError: %d\n", GetLastError());
        fprintf(stderr, "sendto() failed!\nreturen value is %d\n", ret);
        goto Exit;
    }

    sendStatus = TRUE;
    fprintf(stderr, "Send successfully!\n");


Exit:
    if(QueryName) {
        free(QueryName);
    }
    if(pPACKHeader) {
        free(pPACKHeader);
    }
    
    return sendStatus;
}

BOOLEAN verifyDomainName(const char *DomainName)        //TODO: add more details about Valid-Verify
{
    BOOLEAN isValid = TRUE;
    int dnLen = strlen(DomainName);

    if(DomainName == NULL || strlen(DomainName) == 0 || strlen(DomainName) > 255) {
        fprintf(stderr, "1\n");
        isValid = FALSE;
    }
    if(DomainName[0] == '.' || ((DomainName[dnLen-1] == '.') && (DomainName[dnLen-2] == '.'))) {
        fprintf(stderr, "2\n");
        isValid = FALSE;
    }
    if(isValid == TRUE) {
        fprintf(stderr, "DomainName is valid!\n");
    }

    return isValid;
}

int lastIsDot(const char *DomainName)
{
    int isDot = 0;
    int index, dnLen = strlen(DomainName);

    if(DomainName[dnLen - 1] != '.') {
        isDot = 1;
    }

    return isDot;
}

void Domain2QueryName(const char *DomainName, char *QueryName)
{
    int dnLen = strlen(DomainName);
    int qnLen = sizeof(QueryName);
    memset(QueryName, 0, qnLen);

    int i = 0, qnIndex = 0;

    for(i = 0; i < dnLen; ++i) {
        if(DomainName[i] == '.') {
            QueryName[qnIndex] = i - qnIndex;
            if(QueryName[qnIndex] > 0) {
                memcpy(QueryName + qnIndex + 1, DomainName + qnIndex, i - qnIndex);     //well done here!
            }
            qnIndex = i + 1;
        }
    }

    if(DomainName[i - 1] != '.') {          //i == dnLen  here
        QueryName[qnIndex] = i - qnIndex;
        memcpy(QueryName + qnIndex + 1, DomainName + qnIndex, i - qnIndex);
        memset(QueryName + i + 1, 0, 1);
    }
    fprintf(stderr, "DomainName to QueryName finished!\n");
    return;
}