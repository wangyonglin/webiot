#ifndef _SERVER_TCP_H_INCLUDE_
#define _SERVER_TCP_H_INCLUDE_
#include <wangyonglin/config.h>
#include <wangyonglin/core.h>
void server_tcp_conf(wangyonglin_socket_t *socket_t);
int server_tcp_start(wangyonglin_socket_t *socket_t);
#endif