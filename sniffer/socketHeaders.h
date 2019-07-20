#ifndef __SOCKETHEADERS_H__
#define __SOCKETHEADERS_H__

//#include <stdint.h>
//#include <sys/types.h>

#ifndef ETH_LEN
#define ETH_LEN 6
#endif

#define MAX_TRANS_UNIT 1500

#ifndef SIO_RCVALL
#define SIO_RCVALL _WSAIOW(IOC_VENDOR,1)
#endif

typedef struct _ethhdr {
    u_char dest[ETH_LEN];
    u_char source[ETH_LEN];
    uint16_t proto;
}Ethhdr;


typedef struct _iphdr {
# if __BYTE_ORDER == __LITTLE_ENDIAN
    uint8_t ihl:4;
    uint8_t version:4;
# elif __BYTE_ORDER == __BIG_ENDIAN
    uint8_t version:4;
    uint8_t ihl:4;
# else
#   error "Adjust your <bits/endian.h> defines"
# endif
    uint8_t tos;
    uint16_t tot_len;
    uint16_t id;
    uint16_t frag_off;
    uint8_t ttl;
    uint8_t protocol;
    uint16_t checksum;
    uint32_t saddr;
    uint32_t daddr;
}Iphdr;


typedef struct _tcphdr {
    uint16_t sport;
    uint16_t dport;
    uint32_t seq;
    uint32_t ack_seq;
# if __BYTE_ORDER == __LITTLE_ENDIAN
    uint16_t res1:4;
    uint16_t doff:4;
    uint16_t fin:1;
    uint16_t syn:1;
    uint16_t rst:1;
    uint16_t psh:1;
    uint16_t ack:1;
    uint16_t urg:1;
    uint16_t res2:2;
# elif __BYTE_ORDER == __BIG_ENDIAN
    uint16_t doff:4;
    uint16_t res1:4;
    uint16_t res2:2;
    uint16_t urg:1;
    uint16_t ack:1;
    uint16_t psh:1;
    uint16_t rst:1;
    uint16_t syn:1;
    uint16_t fin:1;
# else
#   error "Adjust your <bits/endian.h> defines"
# endif
    uint16_t window;
    uint16_t checksum;
    uint16_t urg_ptr;
}Tcphdr;

typedef struct _udphdr {
    uint16_t sport;
    uint16_t dport;
    uint16_t len;
    uint16_t checksum;
}Udphdr;

#endif