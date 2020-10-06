#ifndef _WANGYONGLIN_SOCKET_H_INCLUDE_
#define _WANGYONGLIN_SOCKET_H_INCLUDE_
#include <wangyonglin/config.h>
#include <wangyonglin/core.h>
typedef struct wangyonglin_socket_s wangyonglin_socket_t;

struct wangyonglin_socket_s
{
    /* data */
    char host[16];
    int sockfd;
    int port;
    int backlog;
};
int wangyonglin_socket_master(wangyonglin_socket_t *socket_t);
#endif
