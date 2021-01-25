#ifndef _WANGYONGLIN_EPOLL_H_INCLUDE_
#define _WANGYONGLIN_EPOLL_H_INCLUDE_
#include <wangyonglin/config.h>
#include <wangyonglin/core.h>
typedef struct wangyonglin_epoll_s wangyonglin_epoll_t;
struct wangyonglin_epoll_s
{
    int epfd;
    struct epoll_event events[20];
    int nfds;
    int index;
};

#endif