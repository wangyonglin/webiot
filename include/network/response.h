#ifndef _NETWORK_RESPONSE_H_INCLUDE_
#define _NETWORK_RESPONSE_H_INCLUDE_
#include <wangyonglin/config.h>
#include <wangyonglin/core.h>
#include <evhttp.h>
int  network_response_success(struct evhttp_request * request,const char *reason,char * result);
int  network_response_failure(struct evhttp_request *request, int error, const char *reason);

#endif