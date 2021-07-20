#ifndef WANGYONGLIN_SOCKET_H
#define WANGYONGLIN_SOCKET_H
#include <wangyonglin/linux.h>
#include <wangyonglin/wangyonglin.h>
typedef struct wangyonglin__socket{
    int sockfd;
    uint16_t __hostshort;
    int __backlog;
}wangyonglin__socket_t;
struct wangyonglin__socket * wangyonglin__socket_tcp(struct wangyonglin__config *config, uint16_t __hostshort,int __backlog);
#endif