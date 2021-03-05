#ifndef _HTTPS_RESTFUL_H_INCLUDE_
#define _HTTPS_RESTFUL_H_INCLUDE_
#include <wangyonglin/config.h>
#include <wangyonglin/core.h>
#include <https/response.h>
typedef struct https_callback_s https_callback_t;
typedef struct https_info
{
    struct event_base *base;
    struct evhttp *httpd;
} https_info;

struct https_callback_s
{
    void (*addcallback)(struct evhttp *http, wangyonglin_socket_t *sock);
};

int https_restful_appcation(wangyonglin_signal_t *signal_t);
char *https_restful_params(https_response_t *response, const char *query_char);
#endif