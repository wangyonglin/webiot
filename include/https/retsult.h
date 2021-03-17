#ifndef _WANGYONGLIN_HTTPS_RETSULT_H_INCLUDE_
#define _WANGYONGLIN_HTTPS_RETSULT_H_INCLUDE_
#include <wangyonglin/config.h>
#include <wangyonglin/core.h>
#include <cjson/json.h>
#include <evhttp.h>
int wangyonglin_https_retsult_success(struct evhttp_request *request,cJSON *text,const char *format, ...);
int wangyonglin_https_retsult_failure(struct evhttp_request *request, int code, const char *format, ...);

#endif