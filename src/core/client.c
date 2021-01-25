#include <wangyonglin/config.h>
#include <wangyonglin/core.h>

void wangyonglin_sockfd_add(wangyonglin_sockfd_t *sockfd_t, int sockfd)
{
    if (sockfd_t == NULL)
        return;
    for (int i = 0; i < (sizeof(sockfd_t->sockfds) / sizeof(int)); i++)
    {
        if (sockfd_t->sockfds[i] == 0x00)
        {
            sockfd_t->sockfds[i] = sockfd;
            return;
        }
    }
}
void wangyonglin_sockfd_del(wangyonglin_sockfd_t *sockfd_t, int sockfd)
{
    if (sockfd_t == NULL)
        return;
    for (int i = 0; i < (sizeof(sockfd_t->sockfds) / sizeof(int)); i++)
    {
        if (sockfd_t->sockfds[i] == sockfd)
        {
            sockfd_t->sockfds[i] = 0x00;
            return;
        }
    }
}
int wangyonglin_sockfd_count(wangyonglin_sockfd_t *sockfd_t)
{
    if (sockfd_t == NULL)
        return -1;
    int ret = 0;
    for (int i = 0; i < (sizeof(sockfd_t->sockfds) / sizeof(int)); i++)
    {

        if (sockfd_t->sockfds[i] != 0x00)
        {
            ret++;
        }
    }
    return ret;
}
void wangyonglin_sockfd_clear(wangyonglin_sockfd_t *sockfd_t)
{
    if (sockfd_t == NULL)
        return;
    bzero(sockfd_t, sizeof(sockfd_t));
}
