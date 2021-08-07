#ifndef _WANGYONGLIN_HTTPS_RETSULT_H_INCLUDE_
#define _WANGYONGLIN_HTTPS_RETSULT_H_INCLUDE_
#include <wangyonglin/linux.h>
#include <wangyonglin/wangyonglin.h>
#include <cjson/json.h>
#include <evhttp.h>
int https__retsult_success(configify_t *config,struct evhttp_request *request,cJSON *text,const char *format, ...);
int https__retsult_failure(configify_t *config,struct evhttp_request *request, int code, const char *format, ...);

#endif