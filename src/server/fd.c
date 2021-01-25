#include <wangyonglin/config.h>
#include <wangyonglin/core.h>
//最大连接数
#define MAXCLIENT 100
//客户端文件描述符 数组
int clientdfs[MAXCLIENT];
//添加一个描述符
int addNewFd(wangyonglin_client_t *client_t)
{

    pthread_mutex_lock(&client_t->mutex_t);
    for (int i = 0; i < MAXCLIENT; i++)
    {
        if (clientdfs[i] == 0)
        {
            printf("\t添加成功！索引%d 句柄 %d \n", i, client_t->sockfd);
            clientdfs[i] = client_t->sockfd;
            //这里互斥锁解锁 需要在 return 之前 ，刚刚出现了bug,就是没有解锁导致后面无法继续。
            pthread_mutex_unlock(&client_t->mutex_t);
            return 1;
        }
        else if (i == MAXCLIENT - 1 && clientdfs[i] != 0)
        {
            pthread_mutex_unlock(&client_t->mutex_t);
            return -1;
        }
    }
}
//删除一个描述符
void rmFd(wangyonglin_client_t *client_t)
{
    pthread_mutex_lock(&client_t->mutex_t);
    for (int i = 0; i < MAXCLIENT; i++)
    {
        if (clientdfs[i] == client_t->sockfd)
        {
            clientdfs[i] = 0;
        }
    }
    pthread_mutex_unlock(&client_t->mutex_t);
}

//发送到所有客户端
void sendToAll(wangyonglin_client_t *client_t, uint8_t *data, int size)
{
    wangyonglin_epoll_t *epoll_t = &client_t->epoll_t;

    pthread_mutex_lock(&client_t->mutex_t);
    for (int i = 0; i < MAXCLIENT; i++)
    {
        if (client_t->sockfd != clientdfs[i] && clientdfs[i] != 0)
        {

            printf("\t待发送数据：%s 索引是%d 句柄 %d\n", data, clientdfs[i], client_t->sockfd);
            int sRe = send(clientdfs[i], data, size, 0);
            printf("\t发送到 句柄 %d,发送结果:%d\n", clientdfs[i], sRe);
        }
    }
    pthread_mutex_unlock(&client_t->mutex_t);
}
