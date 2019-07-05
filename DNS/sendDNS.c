#include <stdio.h>
#include <windows.h>
#include <winsock2.h>
#include "dnsHeader.h"


BOOLEAN sendDNS();
void Domain2QueryName(const char *DomainName, char *QueryName);

int main()
{    
    //test git proxy unset
    return 0;
}

BOOLEAN sendDNS(SOCKET *pSocket, const char *DomainName)	//DNS server is 202.114.0.131 for default
{
    BOOLEAN sendStatus = FALSE;
    unsigned int DomainNameLen = strlen(DomainName);
    unsigned int QueryNameLen = DomainNameLen + 2;
}

void Domain2QueryName(const char * DomainName, char *QqueryName)
{

}
