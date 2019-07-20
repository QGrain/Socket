
#include "api.h"


void pkt_dump(char *buf, int buf_size, int name_number)
{
    char filename[256], temp_name[32];
    strcpy(filename, "./dump/");
    itoa(name_number, temp_name, 10);
    strcat(temp_name, ".txt");
    strcat(filename, temp_name);
    FILE *fp = fopen(filename, "r");
    
    if(fp == NULL) {
        fprintf(stderr, "Failed to dump the %d packet with file %s!\n", name_number, filename);
        goto Exit;
    }

    

Exit:
    if(fp) {
        fclose(fp);
    }
    return;
}