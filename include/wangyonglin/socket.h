#ifndef INCLUDE_WANGYONGLIN_SOCKET_H
#define INCLUDE_WANGYONGLIN_SOCKET_H
#include <wangyonglin/linux.h>
#include <wangyonglin/wangyonglin.h>
typedef struct{
    int sockfd;
    uint16_t __hostshort;
    int __backlog;
}sockify_t;
sockify_t * sockify_tcp(configify_t *config, uint16_t __hostshort,int __backlog);
#endif