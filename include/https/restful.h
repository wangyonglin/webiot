#ifndef _HTTPS_RESTFUL_H_INCLUDE_
#define _HTTPS_RESTFUL_H_INCLUDE_
#include <wangyonglin/config.h>
#include <wangyonglin/core.h>
#include <https/response.h>
typedef struct https_restful_s https_restful_t;
typedef struct https_callback_s https_callback_t;
typedef struct https_info
{
	struct event_base *base;
	struct evhttp *httpd;
} https_info;

struct https_restful_s
{
    wangyonglin_socket_t socket_t;
    wangyonglin_pipe_t pipe;
};

struct https_callback_s
{
    void (*addcallback)(struct evhttp *http,wangyonglin_socket_t * sock);
};

void https_restful_conf(https_restful_t *restful);
int https_restful_start(https_restful_t *restful);
char *https_restful_params(https_response_t *response, const char *query_char);
#endif