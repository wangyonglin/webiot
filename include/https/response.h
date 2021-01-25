#ifndef _HTTPS_RESPONSE_H_INCLUDE_
#define _HTTPS_RESPONSE_H_INCLUDE_
#include <wangyonglin/config.h>
#include <wangyonglin/core.h>
#include <cjson/json.h>
typedef struct https_response_s https_response_t;
typedef struct https_result_s https_result_t;
struct https_result_s
{
    /* data */
    int code;
    const char * reason;
    cJSON * result;
    char timestamp[20];
};

struct https_response_s
{
    struct evhttp_request *request;
    struct evbuffer *evbuf;
    struct evkeyvalq *params;
    cJSON * root;
    struct https_result_s  result;
    char * out;
};

int https_response_send(https_response_t *response);
int https_response_success(https_response_t *response, cJSON *result);
int https_response_failure(https_response_t *response, int error, const char *reason);
#endif