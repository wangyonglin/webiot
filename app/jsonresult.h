#ifndef _APP_JSONRESULT_H_INCLUDE_
#define _APP_JSONRESULT_H_INCLUDE_
#include <wangyonglin/config.h>
#include <wangyonglin/core.h>
#include <cjson/json.h>




int  wangyonglin_jsonresult_success(struct evhttp_request * request,const char *reason,char * result);
int  wangyonglin_jsonresult_failure(struct evhttp_request *request, int error, const char *reason);
#endif /**_APP_JSONRESULT_H_INCLUDE_**/