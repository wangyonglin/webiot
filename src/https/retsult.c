#include <wangyonglin/linux_config.h>
#include <wangyonglin/wangyonglin.h>
#include <https/retsult.h>

#include <cjson/json.h>
#include <event2/bufferevent_ssl.h>
#include <evhttp.h>

int https__retsult_success(struct wangyonglin__config *config, struct evhttp_request *request, cJSON *text, const char *format, ...)
{
    evhttp_add_header(request->output_headers, "Content-Type", "application/json;charset=UTF-8");
    evhttp_add_header(request->output_headers, "Connection", "keep-alive");
    va_list args;
    va_start(args, format);
    char *reason = (char *)calloc(1, 512);
    sprintf(reason, format, args);
    struct evbuffer *evb = NULL;
    char timestamp[20] = {0};
    time__timestamp(config, timestamp, 20);

    /* 输出 JSON*/
    cJSON *root = cJSON_CreateObject(); //创建一个对象
    if (!root)
        return -1;

    cJSON_AddTrueToObject(root, "success");
    cJSON_AddStringToObject(root, "reason", reason);
    if (text == NULL)
        cJSON_AddStringToObject(root, "result", "");
    else
        cJSON_AddItemToObject(root, "result", text);
    cJSON_AddNumberToObject(root, "errcode", 200);
    cJSON_AddStringToObject(root, "timestamp", timestamp);
    char *out = cJSON_Print(root);
    evb = evbuffer_new();
    evbuffer_add(evb, out, strlen(out));
    evhttp_send_reply(request, 200, reason, evb);
    if (evb)
        evbuffer_free(evb);
    free(reason);
    free(out);
    va_end(args);
    cJSON_Delete(root);
    return 0;
}

int https__retsult_failure(struct wangyonglin__config *config, struct evhttp_request *request, int code, const char *format, ...)
{
    evhttp_add_header(request->output_headers, "Content-Type", "application/json;charset=UTF-8");
    evhttp_add_header(request->output_headers, "Connection", "keep-alive");
    va_list args;
    va_start(args, format);
    char *reason = (char *)calloc(1, 512);
    sprintf(reason, format, args);
    struct evbuffer *evb = NULL;
    char timestamp[20] = {0};
    time__timestamp(config, timestamp, 20);
    /* 输出 JSON*/
    cJSON *root = cJSON_CreateObject(); //创建一个对象
    if (!root)
        return -1;

    cJSON_AddFalseToObject(root, "success");
    cJSON_AddStringToObject(root, "reason", reason);
    cJSON_AddStringToObject(root, "result", "");
    cJSON_AddNumberToObject(root, "errcode", code);
    cJSON_AddStringToObject(root, "timestamp", timestamp);
    char *out = cJSON_Print(root);

    evb = evbuffer_new();

    evbuffer_add(evb, out, strlen(out));
    evhttp_send_reply(request, code, reason, evb);

    if (evb)
        evbuffer_free(evb);
    free(reason);
    free(out);
    va_end(args);
    cJSON_Delete(root);
    return 0;
}