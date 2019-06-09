//**********This toolbox is writen for a more convenient programming.********
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//As inet_pton() is not included in ws2tcpip.h
void inet_pton(int FAMILY, char *P_addr, void *N_addr);
void inet_pton(int FAMILY, char *P_addr, void *N_addr)
{
    if (FAMILY == 2) {
        //unsigned long 
    }
    else if (FAMILY == 4) {
        fprintf(stderr, "To be done\n");
        goto Exit;
    }
    else {
        fprintf(stderr, "Error type of FAMILY\n");
        goto Exit;
    }

Exit:
    return;
}