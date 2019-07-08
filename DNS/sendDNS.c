#include <stdio.h>
#include <windows.h>
#include <winsock2.h>
#include "dnsHeader.h"


BOOLEAN sendDNS();
BOOLEAN veriyDomainName(const char *DomainName);
int getDotNum(const char *DomainName);
void Domain2QueryName(const char *DomainName, char *QueryName);



int main()
{   
    BOOLEAN status = FALSE;
    char *DomainName = "baidu.com";
    
    //socket init
    //status = sendDNS(,);

    return 0;
}

BOOLEAN sendDNS(SOCKET *pSocket, const char *DomainName)	//DNS server is 202.114.0.131 for default
{
    BOOLEAN sendStatus = FALSE;
    BOOLEAN dnIsValid = verifyDomainName(DomainName);

    if(pSocket == INVALID_SOCKET || dnIsValid == FALSE) {
        goto Exit;
    }

    int extraLen = getDotNum(DomainName);
    unsigned int DomainNameLen = strlen(DomainName);
    unsigned int QueryNameLen = DomainNameLen + extraLen;

    char *QueryName = (char *)malloc(QueryNameLen);
    Domain2QueryName(DomainName, QueryName);

    DNSHeader *pDNSHeader = (DNSHeader *)malloc(sizeof(DNSHeader *) + QueryNameLen + 4);


Exit:
    if(QueryName) {
        free(QueryName);
    }
    if(pDNSHeader) {
        free(pDNSHeader);
    }
    
    return sendStatus;
}

BOOLEAN verifyDomainName(const char *DomainName)        //TODO: add more details about Valid-Verify
{
    BOOLEAN isValid = TRUE;
    int dnLen = strlen(DomainName);

    if(DomainName == NULL || strlen(DomainName) == 0 || strlen(DomainName) > 255) {
        isValid = FALSE;
    }
    if(DomainName[0] == '.' || ((DomainName[dnLen-1] == '.') && (DomainName[dnLen-2] == '.'))) {
        isValid = FALSE;
    }

    return isValid;
}

int getDotNum(const char *DomainName)
{
    int dotNum = 0;
    int index, dnLen = strlen(DomainName);

    for(index = 0; index < dnLen - 1; ++index) {
        if(DomainName[index] == '.') {
            dotNum++;
        }
    }
    if(DomainName[dnLen - 1] != '.') {
        dotNum = dotNum + 1;
    }

    return dotNum;
}

void Domain2QueryName(const char *DomainName, char *QueryName)
{
    int dnLen = sizeof(DomainName);
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

    if(DomainName[dnLen - 1] != '.') {
        QueryName[qnIndex] = i - qnIndex;       //i == dnLen - 1 here
        memcpy(QueryName + qnIndex + 1, DomainName + qnIndex, i - qnIndex);
        //memset(QqueryName + i?, 0, 1);    TODO...!
    }
    return;
}