#include <wangyonglin/config.h>
#include <wangyonglin/core.h>
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
char *wangyonglin_https_callback_params(struct evhttp_request *request, const char *query_char);

void wangyonglin_https_callback_mosquitto(struct evhttp_request *request, void *arg){
    wangyonglin_signal_t *signal_t = (wangyonglin_signal_t *)arg;
    wangyonglin_logger_success("### IP: %s:%d CODE: %d URL: %s", request->remote_host, request->remote_port, HTTP_OK, evhttp_request_get_uri(request));
    if (request == NULL)
    {
        wangyonglin_https_retsult_failure(request,HTTP_BADREQUEST, "input params is null.");
        return;
    }
    char *sign = NULL;
    char *topic = NULL;
    char *payload = NULL;
    sign = wangyonglin_https_callback_params(request, "sign"); //获取get请求uri中的sign参数
    if (sign == NULL)
    {
        wangyonglin_https_retsult_failure(request, HTTP_BADREQUEST, "request uri no param sign.");
        return;
    }
    topic = wangyonglin_https_callback_params(request, "topic"); //获取get请求uri中的sign参数
    if (topic == NULL)
    {
        wangyonglin_https_retsult_failure(request, HTTP_BADREQUEST, "request uri no param topic.");
        return;
    }
    payload = wangyonglin_https_callback_params(request, "payload"); //获取get请求uri中的data参数
    if (payload == NULL)
    {
        wangyonglin_https_retsult_failure(request, HTTP_BADREQUEST, "request uri no param payload.");

        return;
    }
    cJSON *root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "sign", sign);
    cJSON_AddStringToObject(root, "topic", topic);
    cJSON_AddStringToObject(root, "payload", payload);
    char *json = cJSON_Print(root);
    wangyonglin_string_t string_topic_t = wangyonglin_null_string;
    wangyonglin_string_t string_payload_t = wangyonglin_null_string;
    wangyonglin_string_setting(&string_topic_t, topic);
    wangyonglin_string_setting(&string_payload_t, payload);
    publish_t.topic = string_topic_t;
    publish_t.payload = string_payload_t;
    wangyonglin_signal_queue(signal_t, SIGUSR1, 100, &publish_t);
    wangyonglin_https_retsult_success(request,root,"Show me the money");
}
void wangyonglin_https_callback_notfound(struct evhttp_request *request, void *arg){
    wangyonglin_https_retsult_failure(request,404,"not Found");
}


//解析http头，主要用于get请求时解析uri和请求参数
char *wangyonglin_https_callback_params(struct evhttp_request *request, const char *query_char)
{
    struct evkeyvalq params = {0};
    if (request == NULL || &params == NULL || query_char == NULL)
    {
        wangyonglin_https_retsult_failure(request,HTTP_BADREQUEST,"input params is null.");
        return NULL;
    }
    struct evhttp_uri *decoded = NULL;
    char *query = NULL;
    char *query_result = NULL;
    const char *path;
    const char *uri = evhttp_request_get_uri(request); //获取请求uri
    if (uri == NULL)
    {
        wangyonglin_logger_failure("====line:%d,evhttp_request_get_uri return null\n", __LINE__);

        return NULL;
    }
    //解码uri
    decoded = evhttp_uri_parse(uri);
    if (!decoded)
    {
        wangyonglin_logger_failure("====line:%d,It's not a good URI. Sending BADREQUEST\n", __LINE__);
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
        wangyonglin_logger_failure("====line:%d,evhttp_uri_get_query return null\n", __LINE__);
        return NULL;
    }
    //查询指定参数的值
    evhttp_parse_query_str(query, &params);
    query_result = (char *)evhttp_find_header(&params, query_char);
    return query_result;
}