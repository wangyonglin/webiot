#ifndef _HTTPS_HTTPS_H_INCLUDE_
#define _HTTPS_HTTPS_H_INCLUDE_
#include <wangyonglin/config.h>
#include <wangyonglin/core.h>

#include <evhttp.h>
typedef struct wangyonglin_https_s wangyonglin_https_t;

struct wangyonglin_https_s
{
    int sockfd;
    int port;
    int queue;
    int maxsize;
    int backlog;
    int threads;
    wangyonglin_string_t certificate_chain;
    wangyonglin_string_t private_key;
    SSL_CTX *ctx;
};
typedef struct wangyonglin_https_info
{
    struct event_base *base;
    struct evhttp *httpd;
    struct evhttp_bound_socket *handle;
} wangyonglin_https_info;

int wangyonglin_https_application(wangyonglin_signal_t *signal_t);
#endif