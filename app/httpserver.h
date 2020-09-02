#ifndef _APP_HTTPSERVER_H_INCLUDE_
#define _APP_HTTPSERVER_H_INCLUDE_
#include <wangyonglin/config.h>
#include <wangyonglin/core.h>
#include <evhttp.h>
#include <event.h>
#include "event2/http.h"
#include "event2/event.h"
#include "event2/buffer.h"
#include "event2/bufferevent.h"
#include "event2/bufferevent_compat.h"
#include "event2/http_struct.h"
#include "event2/http_compat.h"
#include "event2/util.h"
#include "event2/listener.h"

typedef struct httpd_info{
	struct event_base *base;
	struct evhttp *httpd;
}httpd_info;

int wangyonglin_httpserver_create(uint16_t __hostshort,int __n);
int wangyonglin_httpserver_build(int __fd,uint16_t __nthreads,int __timeout,const char *path,void * cb_arg);


char * wangyonglin_httpserver_header(struct evhttp_request *req,struct evkeyvalq *params,const char *query_char);






#endif /**_APP_HTTPSERVER_H_INCLUDE_**/