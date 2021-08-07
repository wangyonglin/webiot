#include <wangyonglin/linux.h>
#include <wangyonglin/wangyonglin.h>

sockify_t *sockify_tcp(configify_t *config, uint16_t __hostshort, int __backlog)
{
    sockify_t *socket_t = NULL;
    if (socket_t == NULL)
    {
        socket_t = (sockify_t *)malloc(sizeof(sockify_t *));
    }

    socket_t->__hostshort = __hostshort;
    socket_t->__backlog = __backlog;
    if ((socket_t->sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) /*建立一个流式套接字*/
    {
        logify_printf(config, LOG_ERR, "create socket error: %s(errno: %d)\n", strerror(errno), errno);
        return NULL;
    }

    /*设置服务端地址*/
    struct sockaddr_in sockaddr;
    bzero(&sockaddr, sizeof(struct sockaddr_in));
    sockaddr.sin_family = AF_INET;                    /*AF_INET表示 IPv4 Intern 协议*/
    sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);     /*INADDR_ANY 可以监听任意IP */
    sockaddr.sin_port = htons(socket_t->__hostshort); /*设置端口*/
    socklen_t socklen = sizeof(struct sockaddr_in);
    int opt = 1;
    // sockfd为需要端口复用的套接字
    setsockopt(socket_t->sockfd, SOL_SOCKET, SO_REUSEADDR, (const void *)&opt, sizeof(opt));
    /*绑定地址结构到套接字描述符*/
    if (bind(socket_t->sockfd, (struct sockaddr *)&sockaddr, socklen) == -1)
    {

        logify_printf(config, LOG_ERR, "bind socket error: %s(errno: %d) sin_port %d \n", strerror(errno), errno, socket_t->__hostshort);
        return NULL;
    }

    /*设置监听队列，这里设置为1，表示只能同时处理一个客户端的连接*/
    if (listen(socket_t->sockfd, socket_t->__backlog) == -1)
    {
        logify_printf(config, LOG_ERR, "listen socket error: %s(errno: %d)\n", strerror(errno), errno);

        return NULL;
    }
    int flags;
    if ((flags = fcntl(socket_t->sockfd, F_GETFL, 0)) < 0 || fcntl(socket_t->sockfd, F_SETFL, flags | O_NONBLOCK) < 0)
        return NULL;
    return socket_t;
}

void sockify_cleaup(sockify_t *socket_t)
{
    if (socket_t != NULL)
    {
        free(socket_t);
    }
}