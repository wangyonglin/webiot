#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>  // open function
#include <unistd.h> // close function
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>
#include <sys/epoll.h>
typedef int wangyonglin_sockfd_t;

void server_client_add(wangyonglin_sockfd_t *sockfd_t, int sockfd)
{
    if (sockfd_t == NULL)
        return;
    for (int i = 0; i < (sizeof(sockfd_t)); i++)
    {
        sockfd_t[] = socket;
    }
}
void server_client_del(wangyonglin_client_handle_t *handle_t, int sockfd)
{
    if (handle_t == NULL)
        return;
    for (int i = 0; i < (sizeof(handle_t->items) / sizeof(int)); i++)
    {
        if (handle_t->items[i] == sockfd)
        {
            handle_t->items[i] = 0x00;
            return;
        }
    }
}
int server_client_size(wangyonglin_client_handle_t *handle_t)
{
    if (handle_t == NULL)
        return -1;
    int ret = 0;
    for (int i = 0; i < (sizeof(handle_t->items) / sizeof(int)); i++)
    {

        if (handle_t->items[i] != 0x00)
        {
            ret++;
        }
    }
    return ret;
}
void server_client_clear(wangyonglin_client_handle_t *handle_t)
{
    if (handle_t == NULL)
        return;
    bzero(handle_t, sizeof(handle_t));
}
int main(void)
{
    wangyonglin_client_handle_t handle_t;
    bzero(&handle_t, sizeof(wangyonglin_client_handle_t));
    server_client_add(&handle_t, 2);
    server_client_add(&handle_t, 2);
    server_client_clear(&handle_t);
    server_client_add(&handle_t, 2);
    server_client_del(&handle_t, 2);
    server_client_add(&handle_t, 2);

    int rc = server_client_size(&handle_t);
    printf("\r%d\n", rc);
    return EXIT_SUCCESS;
}