#ifndef _WANGYONGLIN_HTTPS_CALLBACK_H_INCLUDE_
#define _WANGYONGLIN_HTTPS_CALLBACK_H_INCLUDE_
#include <wangyonglin/config.h>
#include <wangyonglin/wangyonglin.h>
void https__callback_mosquitto(struct evhttp_request *request, void *arg);
void https__callback_notfound(struct evhttp_request *request, void *arg);
char *wangyonglin_https_callback_params(struct evhttp_request *request, const char *query_char);
#endif