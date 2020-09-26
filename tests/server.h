#ifndef _WANGYONGLIN_SERVER_H_INCLUDE_
#define _WANGYONGLIN_SERVER_H_INCLUDE_
typedef struct wangyonglin_server_s wangyonglin_server_t;
typedef struct wangyonglin_client_s wangyonglin_client_t;
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <poll.h>
#include <sys/epoll.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <errno.h>
#include <pthread.h>
#include <unistd.h>
 #include <fcntl.h>
 struct wangyonglin_client_s
{
    int sockfd;
    struct sockaddr_in addr;
    socklen_t socklen;
    void *(*recv)(struct wangyonglin_client_s *client,uint8_t * data,int len);
};


struct wangyonglin_server_s
{
    int sockfd;
    uint16_t port;
    int backlog;
    int epfd;
    int epsize;
    struct epoll_event event;
    int eptimeout;
    struct wangyonglin_client_s client;
};


wangyonglin_server_t *wangyonglin_server_create(uint16_t __hostshort);
int wangyonglin_server_epoll(wangyonglin_server_t *server, int count, int timeout, void * (*recv) (struct wangyonglin_client_s *client,uint8_t * data,int len));
int wangyonglin_server_accept(wangyonglin_server_t *server);

#endif /**_WANGYONGLIN_SERVER_H_INCLUDE_**/
