#ifndef _HTTPS_HTTPS_H_INCLUDE_
#define _HTTPS_HTTPS_H_INCLUDE_
#include <wangyonglin/linux.h>
#include <wangyonglin/wangyonglin.h>

#include <evhttp.h>
typedef struct https__request https__request_t;
typedef struct wangyonglin_https_s wangyonglin_https_t;
typedef struct https__param https__param_t;
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
struct https__param
{
    struct wangyonglin__config *config;
    wangyonglin_signal_t *signal_t;
};
struct https__request
{
    wangyonglin_string_t sign;
    wangyonglin_string_t topic;
    wangyonglin_string_t payload;
    wangyonglin_signal_t *signal_t;
    struct wangyonglin__config *config;
    struct evhttp_request *request;
    const char *query_char;
};
int https__application(struct wangyonglin__config *config, wangyonglin_signal_t *signal_t);
void https__success(https__request_t *request_t, const char *format, ...);
void https__failure(https__request_t *request_t, int errcode, const char *format, ...);
#endif