#include <wangyonglin/config.h>
#include <wangyonglin/core.h>
#include <https/https.h>
#include <cjson/json.h>
#define HTTPD_SIGNATURE "www.wangyonglin.com"

int https_response_send(https_response_t *response)
{
    struct https_result_s *result = &response->result;
    /* 输出到客户端 */
    // evhttp_add_header(request->output_headers, "Author", "admin@wangyonglin.com");
    struct evhttp_request *request = response->request;
    evhttp_add_header(request->output_headers, "Service", HTTPD_SIGNATURE);
    evhttp_add_header(request->output_headers, "Content-Type", "application/json;charset=UTF-8");
    evhttp_add_header(request->output_headers, "Connection", "keep-alive");

    response->evbuf = evbuffer_new();
    if (!response->evbuf)
    {
        printf("create evbuffer failed!\n");
        return -1;
    }

    evbuffer_add_printf(response->evbuf, response->out);
    evhttp_send_reply(request, result->code, result->reason, response->evbuf);
    evbuffer_free(response->evbuf);

    return 0;
}

int https_response_success(https_response_t *response, cJSON *text)
{
    struct https_result_s *result = &response->result;
    result->code = 200;
    result->reason = "ok";
    result->result = text;
    wangyonglin_localtime_timestamp(result->timestamp);

    /* 输出 JSON*/
    response->root = cJSON_CreateObject(); //创建一个对象
    if (!response->root)
        return -1;

    cJSON_AddTrueToObject(response->root, "success");
    cJSON_AddStringToObject(response->root, "reason", result->reason);
    cJSON_AddItemToObject(response->root, "result", result->result);
    cJSON_AddNumberToObject(response->root, "errcode", result->code);
    cJSON_AddStringToObject(response->root, "timestamp", result->timestamp);
    response->out = cJSON_Print(response->root);
    cJSON_Delete(response->root);
    return 0;
}
int https_response_failure(https_response_t *response, int error, const char *reason)
{
    struct https_result_s *result = &response->result;
    result->code = error;
    result->reason = reason;
    wangyonglin_localtime_timestamp(result->timestamp);

    /* 输出 JSON*/
    response->root = cJSON_CreateObject(); //创建一个对象
    if (!response->root)
        return -1;

    cJSON_AddFalseToObject(response->root, "success");
    cJSON_AddStringToObject(response->root, "reason", result->reason);
    cJSON_AddStringToObject(response->root, "result", "");
    cJSON_AddNumberToObject(response->root, "errcode", result->code);
    cJSON_AddStringToObject(response->root, "timestamp", result->timestamp);
    response->out = cJSON_Print(response->root);

    cJSON_Delete(response->root);
    return 0;
}