#ifndef _WANGYONGLIN_CLIENT_H_INCLUDE_
#define _WANGYONGLIN_CLIENT_H_INCLUDE_
#include <wangyonglin/config.h>
#include <wangyonglin/core.h>

typedef struct wangyonglin_client_s wangyonglin_client_t;
typedef struct wangyonglin_sockfd_s
{
    int sockfds[1024];
}wangyonglin_sockfd_t;
struct wangyonglin_client_s
{
    int sockfd;
    struct sockaddr_in addr;
    wangyonglin_sockfd_t sockfd_t[1024];
    pthread_mutex_t mutex_t;
    wangyonglin_epoll_t epoll_t;
    wangyonglin_pipe_t pipe_t;
};
void wangyonglin_sockfd_add(wangyonglin_sockfd_t *sockfd_t, int sockfd);
void wangyonglin_sockfd_del(wangyonglin_sockfd_t *sockfd_t, int sockfd);
int wangyonglin_sockfd_count(wangyonglin_sockfd_t *sockfd_t);
void wangyonglin_sockfd_clear(wangyonglin_sockfd_t *sockfd_t);
#endif