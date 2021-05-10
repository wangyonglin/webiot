#include <wangyonglin/linux.h>
#include <wangyonglin/wangyonglin.h>
#include <https/https.h>
#include <https/retsult.h>
#include <mosquitto/mosquitto.h>
#include <https/callback.h>
wangyonglin_mosquitto_publish_t publish_t;
/**
 * // Decode the payload 
    struct evbuffer *buf = evhttp_request_get_input_buffer(req);
    evbuffer_add(buf, "", 1); // NUL-terminate the buffer 
    char *payload = (char *)evbuffer_pullup(buf, -1);
    int post_data_len = evbuffer_get_length(buf);
    char request_data_buf[4096] = {0};
    memcpy(request_data_buf, payload, post_data_len);
    printf("[post_data][%d]=\n %s\n", post_data_len, payload);
    */
char *https__callback_params(https__request_t *request_t, struct evhttp_request *request, const char *query_char);

void https__callback_mosquitto(struct evhttp_request *request, void *arg)
{

    https__request_t *request_t = (https__request_t *)arg;
    request_t->request = request;
    struct wangyonglin__config * config = request_t->config;
    wangyonglin__logger(config, LOG_INFO, "IP: %s:%d CODE: %d URL: %s", request->remote_host, request->remote_port, HTTP_OK, evhttp_request_get_uri(request));
    if (request == NULL)
    {
        https__failure(request_t, HTTP_BADREQUEST, "input params is null.");
        return;
    }
    char *sign = NULL;
    char *topic = NULL;
    char *payload = NULL;
    sign = https__callback_params(request_t, request, "sign"); //获取get请求uri中的sign参数
    if (sign == NULL || strlen(sign) > 20)
    {
        if (sign == NULL)
            https__failure(request_t, HTTP_BADREQUEST, "request uri no param sign.");
        else
            https__failure(request_t, HTTP_BADREQUEST, "request uri  param > 20 sign.");
        return;
    }
    topic = https__callback_params(request_t, request, "topic"); //获取get请求uri中的sign参数
    if (topic == NULL || strlen(topic) > 20)
    {
        if (topic == NULL)
            https__failure(request_t, HTTP_BADREQUEST, "request uri no param topic.");
        else
            https__failure(request_t, HTTP_BADREQUEST, "request uri  param > 20 topic.");
        return;
    }
    payload = https__callback_params(request_t, request, "payload"); //获取get请求uri中的data参数
    if (payload == NULL || strlen(payload) > 20)
    {
        if (payload == NULL)
            https__failure(request_t, HTTP_BADREQUEST, "request uri no param payload.");
        else
            https__failure(request_t, HTTP_BADREQUEST, "request uri  param > 20 payload.");
        return;
    }

    wangyonglin_string_t string_sign_t = wangyonglin_null_string;
    wangyonglin_string_t string_topic_t = wangyonglin_null_string;
    wangyonglin_string_t string_payload_t = wangyonglin_null_string;
    wangyonglin_string_setting(&string_sign_t, sign);
    wangyonglin_string_setting(&string_topic_t, topic);
    wangyonglin_string_setting(&string_payload_t, payload);
    request_t->sign = string_sign_t;
    request_t->topic = string_topic_t;
    request_t->payload = string_payload_t;
    //wangyonglin_signal_queue(signal_t, SIGUSR1, 100, request_t);
    wangyonglin__message_send(config,SIGUSR1,100, request_t);
}
void https__callback_notfound(struct evhttp_request *request, void *arg)
{
    https__request_t request_t;
    request_t.request = request;
    request_t.config = (struct wangyonglin__config *)arg;
    https__failure(&request_t, 404, "not Found");
}

//解析http头，主要用于get请求时解析uri和请求参数
char *https__callback_params(https__request_t *request_t, struct evhttp_request *request, const char *query_char)
{
    struct evkeyvalq params = {0};
    if (request == NULL || &params == NULL || query_char == NULL)
    {
        https__failure(request_t, HTTP_BADREQUEST, "input params is null.");
        return NULL;
    }
    struct evhttp_uri *decoded = NULL;
    char *query = NULL;
    char *query_result = NULL;
    const char *path;
    const char *uri = evhttp_request_get_uri(request); //获取请求uri
    if (uri == NULL)
    {
        wangyonglin__logger(request_t->config, LOG_INFO, "====line:%d,evhttp_request_get_uri return null\n", __LINE__);

        return NULL;
    }
    //解码uri
    decoded = evhttp_uri_parse(uri);
    if (!decoded)
    {
        wangyonglin__logger(request_t->config, LOG_INFO, "====line:%d,It's not a good URI. Sending BADREQUEST\n", __LINE__);
        evhttp_send_error(request, HTTP_BADREQUEST, 0);
        return NULL;
    }
    //获取uri中的path部分
    path = evhttp_uri_get_path(decoded);
    if (path == NULL)
    {
        path = "/";
    }
    //获取uri中的参数部分
    query = (char *)evhttp_uri_get_query(decoded);
    if (query == NULL)
    {
        wangyonglin__logger(request_t->config, LOG_INFO, "====line:%d,evhttp_uri_get_query return null\n", __LINE__);
        return NULL;
    }
    //查询指定参数的值
    evhttp_parse_query_str(query, &params);
    query_result = (char *)evhttp_find_header(&params, query_char);
    return query_result;
}
