#ifndef _SERVER_FD_H_INCLUDE_
#define _SERVER_FD_H_INCLUDE_
#include <wangyonglin/config.h>
#include <wangyonglin/core.h>
int addNewFd(wangyonglin_client_t *client_t);
void rmFd(wangyonglin_client_t *client_t);
void sendToAll(wangyonglin_client_t *client_t, uint8_t *data, int size);
#endif