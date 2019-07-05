#pragma pack(push, 1)

typedef struct dnsHeader
{
    //transaction ID, 2 bytes
    unsigned short Trans_ID;    //Transaction ID

    //Flags, 2 bytes, network endian's sequence is (LSB)QR-opcode-TC-RD- 
    unsigned char RD : 1;       //Recursion Desire, 1 for don't query recursively
    unsigned char TC : 1;       //Truncated, 0 for message is not truncated
    unsigned char opcode : 4;   //option code, 0 for standard query, 1 for reverse query, 2 for server condition query
    unsigned char QR : 1;       //Query Response, 0 for query is message

    unsigned char ReplyCode : 4;//Reply code, 4'b0000 for no error
    unsigned char Zero : 3;     //Reserved, has to be 3'b000
    unsigned char RA : 1;       //Recursion Available, 1 for server can do recursive queries

    //NUMBER SECTION, 8 bytes
    unsigned short Qestions;    //Number of questions
    unsigned short AnswerRRs;   //Number of answer resouces
    unsigned short AuthorityRRs;//Number of authority resources
    unsigned short AddtionalRRs;//Number of addtional resources
} DNSHeader;


#pragma pack(pop)
