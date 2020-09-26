#include "server.h"
void *____callback(struct wangyonglin_client_s *client, uint8_t *data, int len);
int main()
{
    int rc = 0;
    wangyonglin_server_t *server = wangyonglin_server_create(7132);
    if (server == NULL)
    {
        fprintf(stderr, "\t wangyonglin_server_create NULL \n");
        exit(EXIT_FAILURE);
    }
    fprintf(stdout, "\t wangyonglin_server_create OK \n");
    rc = wangyonglin_server_epoll(server, 500, 3000, ____callback);
    for (;;)
        ;
    return rc;
}
void *____callback(struct wangyonglin_client_s *client, uint8_t *data, int len)
{
    fprintf(stdout, "\t %s %d %d \n", data, len,client->addr.sin_port);
}