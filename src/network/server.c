#include <wangyonglin/config.h>
#include <wangyonglin/core.h>
#include <network/server.h>
#define MAXSLEEP 128
#define MAXBUF 1024
void ____epoll_pool(void *arg);
void __exit(network_server_t *server);
int ____server_recv(struct network_client_s *client, unsigned char *buf, int len);

network_server_t *network_server_create(uint16_t __hostshort)
{
    int len = sizeof(network_server_t);
    network_server_t *server = (network_server_t *)malloc(len);
    if (server == NULL)
    {
        fprintf(stderr, "network_server_t failed \n");
        return NULL;
    }
    server->port = __hostshort;
    if ((server->sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) /*建立一个流式套接字*/
    {
        printf("create socket error: %s(errno: %d)\n", strerror(errno), errno);
        free(server);
        return NULL;
    }

    /*设置服务端地址*/
    struct sockaddr_in sockaddr;
    bzero(&sockaddr, sizeof(struct sockaddr_in));
    sockaddr.sin_family = AF_INET;                /*AF_INET表示 IPv4 Intern 协议*/
    sockaddr.sin_addr.s_addr = htonl(INADDR_ANY); /*INADDR_ANY 可以监听任意IP */
    sockaddr.sin_port = htons(server->port);      /*设置端口*/
    socklen_t socklen = sizeof(struct sockaddr_in);
    int opt = 1;
    // sockfd为需要端口复用的套接字
    setsockopt(server->sockfd, SOL_SOCKET, SO_REUSEADDR, (const void *)&opt, sizeof(opt));
    /*绑定地址结构到套接字描述符*/
    if (bind(server->sockfd, (struct sockaddr *)&sockaddr, socklen) == -1)
    {
        printf("bind socket error: %s(errno: %d)\n", strerror(errno), errno);
        free(server);
        return NULL;
    }

    /*设置监听队列，这里设置为1，表示只能同时处理一个客户端的连接*/
    if (listen(server->sockfd, server->backlog) == -1)
    {
        printf("listen socket error: %s(errno: %d)\n", strerror(errno), errno);
        free(server);
        return NULL;
    }

    return server;
}

int network_server_epoll(network_server_t *server, int count, int timeout, void (*recv)(struct network_client_s *client, uint8_t *data, int len))
{
    int rc = 0;
    server->epsize = count;
    server->eptimeout = timeout;
    // epoll 初始化
    server->epfd = epoll_create(server->epsize);

    server->event.events = EPOLLIN | EPOLLET;
    server->event.data.fd = server->sockfd;
    server->client.recv = recv;
    pthread_t id;
    pthread_create(&id, NULL, (void *)____epoll_pool, server);

    return rc;
}
void ____epoll_pool(void *arg)
{
    network_server_t *server = (network_server_t *)arg;

    struct epoll_event eventList[server->epsize];
    int templen = sizeof(unsigned char) * 1024;
    unsigned char *tempbuf = (unsigned char *)malloc(templen);
    //add Event
    if (epoll_ctl(server->epfd, EPOLL_CTL_ADD, server->sockfd, &server->event) < 0)
    {
        printf("epoll add fail : fd = %d\n", server->sockfd);
        return;
    }
    while (1)
    {
        //epoll_wait
        int ret = epoll_wait(server->epfd, eventList, server->epsize, server->eptimeout);

        if (ret < 0)
        {
            printf("epoll error\n");
            break;
        }
        else if (ret == 0)
        {
            //printf("timeout ...\n");
            continue;
        }
        //直接获取了事件数量,给出了活动的流,这里是和poll区别的关键
        int i = 0;
        for (i = 0; i < ret; i++)
        {
            //错误退出
            if ((eventList[i].events & EPOLLERR) ||
                (eventList[i].events & EPOLLHUP) ||
                !(eventList[i].events & EPOLLIN))
            {
                printf("错误退出 ...\n");
                close(eventList[i].data.fd);
                break;
            }

            if (eventList[i].data.fd == server->sockfd)
            {

                if (network_server_accept(server) >= 0)
                {
                    //将新建立的连接添加到EPOLL的监听中
                    struct epoll_event event;
                    event.data.fd = server->client.sockfd;
                    event.events = EPOLLIN | EPOLLET;
                    epoll_ctl(server->epfd, EPOLL_CTL_ADD, server->client.sockfd, &event);
                }
                else
                {
                    printf("bad accept\n");
                }
            }
            else
            {

                ____server_recv(&server->client, tempbuf, templen);
            }
        }
    }
    free(tempbuf);
    pthread_exit(NULL);
}
int network_server_accept(network_server_t *server)
{

    int rc = -1;

    socklen_t socklen = sizeof(server->client.addr);
    rc = accept(server->sockfd, (struct sockaddr *)&server->client.addr, &socklen);

    if (rc < 0)
    {
        printf("bad accept\n");
        return rc;
    }
    else
    {

        server->client.sockfd = rc;
    }

    return rc;
}
void __exit(network_server_t *server)
{
    close(server->epfd);
    close(server->sockfd);
}

int ____server_recv(struct network_client_s *client, unsigned char *buf, int len)
{
    int flag = fcntl(client->sockfd, F_GETFL, 0);
    flag |= O_NONBLOCK;
    fcntl(client->sockfd, F_SETFL, flag);

    int rc;

    bzero(buf, sizeof(buf));
    rc = recv(client->sockfd, buf, MAXBUF, 0);
    if (rc > 0)
    {

        client->recv(client, buf, rc);
    }

    return rc;
}