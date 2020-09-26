#ifndef _NETWORK_RESTFUL_H_INCLUDE_
#define _NETWORK_RESTFUL_H_INCLUDE_
#include <wangyonglin/config.h>
#include <wangyonglin/core.h>
#include <evhttp.h>

typedef struct network_restful_s network_restful_t;
typedef struct httpd_info
{
	struct event_base *base;
	struct evhttp *httpd;
} httpd_info;
struct network_restful_s
{
	int sockfd;
	int port;
	int backlog;
};
void network_restful_conf(network_restful_t *restful);
void network_restful_notfound(struct evhttp_request *request, void *args);
void network_restful_get(struct evhttp_request *req, void *arg);
void *network_restful_dispatch(void *args);
int network_restful_bind(network_restful_t *restful);
int network_restful_run(network_restful_t *restful);
char *network_restful_params(struct evhttp_request *req, struct evkeyvalq *params, const char *query_char);
void *network_restful_dispatch(void *args);
void netwrok_restful_close(network_restful_t *restful);
#endif
