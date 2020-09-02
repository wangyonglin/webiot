#ifndef _APP_H_INCLUDE_
#define _APP_H_INCLUDE_
#include <wangyonglin/config.h>
#include <wangyonglin/core.h>

typedef struct httpd_info{
	struct event_base *base;
	struct evhttp *httpd;
}httpd_info;

int wangyonglin_http_create(uint16_t __hostshort,int __n);
int wangyonglin_http_build(int __fd,uint16_t __nthreads,int __timeout,const char *path,void * cb_arg);


char * wangyonglin_http_header(struct evhttp_request *req,struct evkeyvalq *params,const char *query_char);
#endif /**_APP_H_INCLUDE_**/
