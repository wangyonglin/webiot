#include <wangyonglin/config.h>
#include <wangyonglin/core.h>
#include <server/tcp.h>

#define MAXLINE 1024
#define OPEN_MAX 100
#define LISTENQ 20
#define SERV_PORT 5000
//最大事件数  epoll event
#define MAXEVENTS 100
#define INFTIM 1000

void server_tcp_pipe(void *args);
void server_tcp_epoll(void *args);
void server_tcp_accpet(wangyonglin_socket_t *socket_t);
void do_client(wangyonglin_client_t *client_t);
int addNewFd(wangyonglin_client_t *client_t);
void rmFd(wangyonglin_client_t *client_t);
void sendToAll(wangyonglin_client_t *client_t, uint8_t *data, int size);
uint8_t data[MAXLINE];
void recv_message(unsigned int sock_fd)
{
    char recv_buf[1024], send_buf[1024];

    memset(recv_buf, 0, sizeof(recv_buf));
    memset(send_buf, 0, sizeof(send_buf));

    recv(sock_fd, recv_buf, sizeof(recv_buf), 0);
    fputs(recv_buf, stdout);
    strcpy(send_buf, recv_buf);
    send(sock_fd, send_buf, sizeof(send_buf), 0);

    return;
}
void server_tcp_conf(wangyonglin_socket_t *socket_t)
{
    socket_t->port = wangyonglin_conf_number("server:port");
    socket_t->backlog = wangyonglin_conf_number("server:backlog");
}

int server_tcp_start(wangyonglin_socket_t *socket_t)
{

    if (wangyonglin_socket_master(socket_t) != 0)
    {
        wangyonglin_log_error(LOG_ERROR, "%d server_tcp_start", __LINE__);
    }
    wangyonglin_log_info("server start ok !");
    pthread_t id;
    pthread_create(&id, NULL, server_tcp_epoll, socket_t);

    return 0;
}

void server_tcp_epoll(void *args)
{

    wangyonglin_socket_t *socket_t = (wangyonglin_socket_t *)args;
    wangyonglin_client_t *client_t = &socket_t->client_t;
    wangyonglin_epoll_t *epoll_t = &client_t->epoll_t;

    int i;
    pthread_mutex_init(&client_t->mutex_t, NULL);
    bzero(&data, MAXLINE);
    ssize_t rc;

    epoll_t->epfd = epoll_create(256);
    struct epoll_event event;
    event.data.fd = socket_t->sockfd;
    event.events = EPOLLIN;
    //注册事件
    epoll_ctl(epoll_t->epfd, EPOLL_CTL_ADD, socket_t->sockfd, &event);
    socklen_t addrlen = sizeof(client_t->addr);
    for (;;)
    {
        //等待epoll事件的发生

        epoll_t->nfds = epoll_wait(epoll_t->epfd, epoll_t->events, MAXEVENTS, -1);
        /*epoll事件错误.*/
        if (epoll_t->nfds < 0)
        {
            printf("epoll event err!");
            break;
        }
        /*无事件返回.*/
        else if (epoll_t->nfds == 0)
        {
            continue;
        }
        /*epoll返回事件.*/
        for (i = 0; i < epoll_t->nfds; ++i)
        {
            /*epoll 错误*/
            if ((epoll_t->events[i].events & EPOLLERR) ||
                (epoll_t->events[i].events & EPOLLHUP) ||
                !(epoll_t->events[i].events & EPOLLIN))
            {
                printf("epoll error\n");
                close(epoll_t->events[i].data.fd);
                exit(-1);
            }
            //half connection
            if (epoll_t->events[i].events & EPOLLRDHUP)
            {
                close(epoll_t->events[i].data.fd);
            }
            /*accept事件*/
            if (epoll_t->events[i].data.fd == socket_t->sockfd)
            {
                server_tcp_accpet(socket_t);
            }
            /*非sock_fd则为其他事件.*/
            else
            {
                recv_message(epoll_t->events[i].data.fd);
            }
        }
    }
}

void server_tcp_accpet(wangyonglin_socket_t *socket_t)
{
    wangyonglin_client_t *client_t = &socket_t->client_t;
    wangyonglin_epoll_t *epoll_t = &client_t->epoll_t;
    wangyonglin_pipe_t *pipe_t = &client_t->pipe_t;

    socklen_t addrlen = sizeof(struct sockaddr);

    client_t->sockfd = accept(socket_t->sockfd, (struct sockaddr *)&client_t->addr, &addrlen);

    if (client_t->sockfd <= 0)
    {
        perror("accept error");
        return;
    }

    //将新建连接加入epoll set
    struct epoll_event event;
    event.data.fd = client_t->sockfd;
    event.events = EPOLLIN | EPOLLET | EPOLLRDHUP;
    epoll_ctl(epoll_t->epfd, EPOLL_CTL_ADD, client_t->sockfd, &event);
}
/*
void server_tcp_pipe(void *args)
{
    uint8_t data[1024];
    int len = 1024;
    int rc;
    wangyonglin_client_t *client_t = (wangyonglin_client_t *)args;
    wangyonglin_sockfd_t *sockfd_t = &client_t->sockfd_t;
    wangyonglin_pipe_t *pipe_t = &client_t->pipe_t;

    for (;;)
    {
        bzero(&data, len);
        if ((rc = wangyonglin_pipe_read(pipe_t, data, len)) > 0)
        {
            printf("\t%s\n", data);
            int count = wangyonglin_sockfd_count(sockfd_t);
            for (int index = 0; index < count; index++)
            {
                send(sockfd_t->sockfds[index], data, strlen(data), 0);
            }
        }
    }
}*/