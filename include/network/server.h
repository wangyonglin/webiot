#ifndef _NETWORK_SERVER_H_INCLUDE_
#define _NETWORK_SERVER_H_INCLUDE_
#include <wangyonglin/config.h>
#include <wangyonglin/core.h>

typedef struct network_server_s network_server_t;
typedef struct network_client_s network_client_t;
struct network_client_s
{
    int sockfd;
    struct sockaddr_in addr;
    void (*recv)(struct network_server_s *client, uint8_t *data, int len);
};

struct network_server_s
{
    int sockfd;
    int port;
    int backlog;
    int epfd;
    int epsize;
    struct epoll_event event;
    int eptimeout;
    struct network_client_s client;
};


network_server_t *network_server_create(uint16_t __hostshort);
int network_server_epoll(network_server_t *server, int count, int timeout, void (*recv)(struct network_client_s *client, uint8_t *data, int len));
int network_server_accept(network_server_t *server);
#endif