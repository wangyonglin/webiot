#ifndef _WANGYONGLIN_SOCKET_H_INCLUDE_
#define _WANGYONGLIN_SOCKET_H_INCLUDE_
#include <wangyonglin/linux_config.h>
#include <wangyonglin/wangyonglin.h>
typedef struct wangyonglin_socket_s wangyonglin_socket_t;
typedef struct wangyonglin_socket_client_s wangyonglin_socket_client_t;
struct wangyonglin_socket_client_s
{
    int sockfd;
    struct sockaddr_in addr;
    fd_set readfds;
    fd_set testfds;
};

struct wangyonglin_socket_s
{
    int sockfd;
    int port;
    int queue;
    int maxsize;
    int backlog;
    wangyonglin_client_t client_t;
};
int wangyonglin_socket_build(wangyonglin_socket_t *socket_t);
ssize_t wangyonglin_socket_send(int sockfd, uint8_t *data, size_t len);
void wangyonglin_socket_setnonblocking(int sockfd);
#endif
