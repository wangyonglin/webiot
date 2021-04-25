#include <wangyonglin/linux_config.h>
#include <wangyonglin/wangyonglin.h>
#include <https/https.h>
#include <https/retsult.h>
#include <https/callback.h>
#include <https/openssl.h>
#include <event2/bufferevent_ssl.h>
#define MYHTTPD_SIGNATURE "wangyonglin v0.1"
void *https__dispatch(void *args);
static struct bufferevent *https__bufferevent_cb(struct event_base *base, void *arg);
int wangyonglin_https_socket(struct wangyonglin__config *config, wangyonglin_https_t *https_t);
//static void login_cb(struct evhttp_request *req, void *arg);
static wangyonglin_https_t *wangyonglin_config_initialization(struct wangyonglin__config *config);
wangyonglin_https_t *wangyonglin_config_initialization(struct wangyonglin__config *config)
{
    //配置 HTTPS 需要的参数
    wangyonglin_https_t *https_t = (wangyonglin_https_t *)calloc(1, sizeof(wangyonglin_https_t));
    // 2. Traverse to a table.
    wangyonglin_conf_table_t *https = wangyonglin_conf_table_in(config->conf, "HTTPS");
    if (!https)
    {
        log__printf(config, LOG_ERR, "missing [https]");
        return NULL;
    }

    // 3. Extract values
    wangyonglin_conf_datum_t port = wangyonglin_conf_int_in(https, "port");
    if (!port.ok)
    {
        log__printf(config, LOG_ERR, "cannot read https.host", "");
        return NULL;
    }

    // 3. Extract values
    wangyonglin_conf_datum_t backlog = wangyonglin_conf_int_in(https, "backlog");
    if (!backlog.ok)
    {
        log__printf(config, LOG_ERR, "cannot read https.backlog", "");
        return NULL;
    }

    // 3. Extract values
    wangyonglin_conf_datum_t threads = wangyonglin_conf_int_in(https, "threads");
    if (!threads.ok)
    {
        log__printf(config, LOG_ERR, "cannot read https.threads", "");
        return NULL;
    }

    // 3. Extract values
    wangyonglin_conf_datum_t certificate_chain = wangyonglin_conf_string_in(https, "certificate_chain");
    if (!certificate_chain.ok)
    {
        log__printf(config, LOG_ERR, "cannot read https.certificate_chain", "");
        return NULL;
    }

    // 3. Extract values
    wangyonglin_conf_datum_t private_key = wangyonglin_conf_string_in(https, "private_key");
    if (!private_key.ok)
    {
        log__printf(config, LOG_ERR, "cannot read https.private_key", "");
        return NULL;
    }
    wangyonglin_string_setting(&https_t->private_key, private_key.u.s);
    wangyonglin_string_setting(&https_t->certificate_chain, certificate_chain.u.s);
    https_t->threads = threads.u.i;
    https_t->backlog = backlog.u.i;
    https_t->port = port.u.i;
    return https_t;
}
int https__application(struct wangyonglin__config *config, wangyonglin_signal_t *signal_t)
{
    https__request_t request_t;
    request_t.config=config;
    request_t.signal_t=signal_t;
    //配置 HTTPS 需要的参数
    wangyonglin_https_t *https_t = wangyonglin_config_initialization(config);
    if (https_t == NULL)
    {
        exit(EXIT_FAILURE);
    }
    /* 选择服务器证书 和 服务器私钥. 1/2 创建SSL上下文环境 ，可以理解为 SSL句柄 */
    https_t->ctx = wangyonglin_openssl_context_create();
    /* 选择服务器证书 和 服务器私钥. 2/2  设置服务器证书 和 服务器私钥 到 OPENSSL ctx上下文句柄中 */
    wangyonglin_openssl_context_configure(https_t->ctx, https_t->certificate_chain.data, https_t->private_key.data);
    /* 配置 SOCKET */
    if (wangyonglin_https_socket(config, https_t) != 0)
    {
        log__printf(config, LOG_ERR, "Couldn't create an socket: exiting");
        return -7;
    }
    pthread_t ths[https_t->threads];
    wangyonglin_https_info info_arr[https_t->threads], *pinfo;
    int i, ret, opt = 1;
    for (i = 0; i < https_t->threads; i++)
    {
        pinfo = &info_arr[i];
        pinfo->base = event_base_new();
        if (pinfo->base == NULL)
        {
            log__printf(config, LOG_ERR, "Couldn't create an event_base: exiting");
            return -8;
        }
        pinfo->httpd = evhttp_new(pinfo->base);
        if (pinfo->httpd == NULL)
        {
            log__printf(config, LOG_ERR, "couldn't create evhttp. exiting.");
            return -9;
        }
        /* 
        使我们创建好的evhttp句柄 支持 SSL加密
        实际上，加密的动作和解密的动作都已经帮
        我们自动完成，我们拿到的数据就已经解密之后的
            */
        evhttp_set_bevcb(pinfo->httpd, https__bufferevent_cb, https_t->ctx);
        evhttp_set_cb(pinfo->httpd, "/mosquitto", https__callback_mosquitto, &request_t);
        evhttp_set_gencb(pinfo->httpd, https__callback_notfound, config);
        /* 设置监听IP和端口 */
        if (evhttp_accept_socket(pinfo->httpd, https_t->sockfd) != 0)
        {
            log__printf(config, LOG_ERR, "evhttp_accept_socket failed! port:%d\n", https_t->port);
            return -10;
        }
        ret = pthread_create(&ths[i], NULL, https__dispatch, pinfo);
    }
    for (i = 0; i < https_t->threads; i++)
    {
        pthread_join(ths[i], NULL);
    }

    return ret;
}

void *https__dispatch(void *args)
{
    wangyonglin_https_info *info = (wangyonglin_https_info *)args;
    event_base_dispatch(info->base);
    event_base_free(info->base);
    evhttp_free(info->httpd);
}

/**
 * This callback is responsible for creating a new SSL connection
 * and wrapping it in an OpenSSL bufferevent.  This is the way
 * we implement an https server instead of a plain old http server.
 */
static struct bufferevent *https__bufferevent_cb(struct event_base *base, void *arg)
{
    struct bufferevent *r;
    SSL_CTX *ctx = (SSL_CTX *)arg;
    SSL *ssl = SSL_new(ctx);
    r = bufferevent_openssl_socket_new(base, -1, ssl, BUFFEREVENT_SSL_ACCEPTING, BEV_OPT_CLOSE_ON_FREE);
    return r;
}

/* This callback gets invoked when we get any http request that doesn't match
 * any other callback.  Like any evhttp server callback, it has a simple job:
 * it must eventually call evhttp_send_error() or evhttp_send_reply().
 */
/*
static void
login_cb(struct evhttp_request *req, void *arg)
{
    struct evbuffer *evb = NULL;
    const char *uri = evhttp_request_get_uri(req);
    struct evhttp_uri *decoded = NULL;

    /* 判断 req 是否是GET 请求 
    if (evhttp_request_get_command(req) == EVHTTP_REQ_GET)
    {
        struct evbuffer *buf = evbuffer_new();
        if (buf == NULL)
            return;
        //  evbuffer_add_printf(buf, "Requested: %s\n", uri);
        // evhttp_send_reply(req, HTTP_OK, "OK", buf);
        wangyonglin_https_retsult_success(req, NULL, NULL);
        return;
    }

    /* 这里只处理Post请求, Get请求，就直接return 200 OK 
    if (evhttp_request_get_command(req) != EVHTTP_REQ_POST)
    {
        evhttp_send_reply(req, 200, "OK", NULL);
        return;
    }

    printf("Got a POST request for <%s>\n", uri);

    //判断此URI是否合法
    decoded = evhttp_uri_parse(uri);
    if (!decoded)
    {
        printf("It's not a good URI. Sending BADREQUEST\n");
        evhttp_send_error(req, HTTP_BADREQUEST, 0);
        return;
    }

    /* Decode the payload
    struct evbuffer *buf = evhttp_request_get_input_buffer(req);
    evbuffer_add(buf, "", 1); /* NUL-terminate the buffer 
    char *payload = (char *)evbuffer_pullup(buf, -1);
    int post_data_len = evbuffer_get_length(buf);
    char request_data_buf[4096] = {0};
    memcpy(request_data_buf, payload, post_data_len);
    printf("[post_data][%d]=\n %s\n", post_data_len, payload);

    /*
       具体的：可以根据Post的参数执行相应操作，然后将结果输出
       ...
   
    //unpack json
    cJSON *root = cJSON_Parse(request_data_buf);
    cJSON *username = cJSON_GetObjectItem(root, "username");
    cJSON *password = cJSON_GetObjectItem(root, "password");

    printf("username = %s\n", username->valuestring);
    printf("password = %s\n", password->valuestring);

    cJSON_Delete(root);

    //packet json
    root = cJSON_CreateObject();

    cJSON_AddStringToObject(root, "result", "ok");
    cJSON_AddStringToObject(root, "sessionid", "xxxxxxxx");

    char *response_data = cJSON_Print(root);
    cJSON_Delete(root);

    /* This holds the content we're sending.

    //HTTP header

    evhttp_add_header(evhttp_request_get_output_headers(req), "Server", MYHTTPD_SIGNATURE);
    evhttp_add_header(evhttp_request_get_output_headers(req), "Content-Type", "text/plain; charset=UTF-8");
    evhttp_add_header(evhttp_request_get_output_headers(req), "Connection", "close");

    evb = evbuffer_new();
    evbuffer_add_printf(evb, "%s", response_data);
    //将封装好的evbuffer 发送给客户端
    evhttp_send_reply(req, HTTP_OK, "OK", evb);

    if (decoded)
        evhttp_uri_free(decoded);
    if (evb)
        evbuffer_free(evb);

    printf("[response]:\n");
    printf("%s\n", response_data);

    free(response_data);
}
*/
int wangyonglin_https_socket(struct wangyonglin__config *config, wangyonglin_https_t *https_t)
{
    if ((https_t->sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) /*建立一个流式套接字*/
    {
        log__printf(config, LOG_ERR, "create socket error: %s(errno: %d)\n", strerror(errno), errno);
        return -1;
    }

    /*设置服务端地址*/
    struct sockaddr_in sockaddr;
    bzero(&sockaddr, sizeof(struct sockaddr_in));
    sockaddr.sin_family = AF_INET;                /*AF_INET表示 IPv4 Intern 协议*/
    sockaddr.sin_addr.s_addr = htonl(INADDR_ANY); /*INADDR_ANY 可以监听任意IP */
    sockaddr.sin_port = htons(https_t->port);     /*设置端口*/
    socklen_t socklen = sizeof(struct sockaddr_in);
    int opt = 1;
    // sockfd为需要端口复用的套接字
    setsockopt(https_t->sockfd, SOL_SOCKET, SO_REUSEADDR, (const void *)&opt, sizeof(opt));
    /*绑定地址结构到套接字描述符*/
    if (bind(https_t->sockfd, (struct sockaddr *)&sockaddr, socklen) == -1)
    {

        log__printf(config, LOG_ERR, "bind socket error: %s(errno: %d) sin_port %d \n", strerror(errno), errno, https_t->port);
        return -1;
    }

    /*设置监听队列，这里设置为1，表示只能同时处理一个客户端的连接*/
    if (listen(https_t->sockfd, https_t->backlog) == -1)
    {
        log__printf(config, LOG_ERR, "listen socket error: %s(errno: %d)\n", strerror(errno), errno);

        return -1;
    }
    int flags;
    if ((flags = fcntl(https_t->sockfd, F_GETFL, 0)) < 0 || fcntl(https_t->sockfd, F_SETFL, flags | O_NONBLOCK) < 0)
        return -1;
    return 0;
}

/**
 * 回应HTTP请求
 **/
void https__success(https__request_t *request_t, const char *format, ...)
{
    evhttp_add_header(request_t->request->output_headers, "Content-Type", "application/json;charset=UTF-8");
    evhttp_add_header(request_t->request->output_headers, "Connection", "keep-alive");
    va_list args;
    va_start(args, format);
    char *message = (char *)calloc(1, 512);
    sprintf(message, format, args);
    struct evbuffer *evb = NULL;
    char timestamp[20] = {0};
    time__timestamp(request_t->config, timestamp, 20);

    cJSON *result = cJSON_CreateObject();
    cJSON_AddStringToObject(result, "sign", request_t->sign.data);
    cJSON_AddStringToObject(result, "topic", request_t->topic.data);
    cJSON_AddStringToObject(result, "payload", request_t->payload.data);
    /* 输出 JSON*/
    cJSON *root = cJSON_CreateObject(); //创建一个对象
    if (!root)
        return;

    cJSON_AddTrueToObject(root, "success");
    cJSON_AddStringToObject(root, "message", message);
    cJSON_AddItemToObject(root, "result", result);
    cJSON_AddNumberToObject(root, "errcode", 200);
    cJSON_AddStringToObject(root, "timestamp", timestamp);
    char *out = cJSON_Print(root);
    evb = evbuffer_new();
    evbuffer_add(evb, out, strlen(out));
    evhttp_send_reply(request_t->request, 200, message, evb);
    if (evb)
        evbuffer_free(evb);
    free(message);
    free(out);
    va_end(args);
    cJSON_Delete(root);
    //cJSON_Delete(result);
}

void https__failure(https__request_t *request_t, int errcode, const char *format, ...)
{
    struct evhttp_request *request  =  request_t->request;
    evhttp_add_header(request->output_headers, "Content-Type", "application/json;charset=UTF-8");
    evhttp_add_header(request->output_headers, "Connection", "keep-alive");
    va_list args;
    va_start(args, format);
    char *message = (char *)calloc(1, 512);
    sprintf(message, format, args);
    struct evbuffer *evb = NULL;
    char timestamp[20] = {0};
    time__timestamp(request_t->config, timestamp, 20);

    /* 输出 JSON*/
    cJSON *root = cJSON_CreateObject(); //创建一个对象
    if (!root)
        return;
  
    cJSON_AddFalseToObject(root, "success");
    cJSON_AddStringToObject(root, "message", message);
    cJSON_AddNullToObject(root, "result");
    cJSON_AddNumberToObject(root, "errcode", errcode);
    cJSON_AddStringToObject(root, "timestamp", timestamp);
    char *out = cJSON_Print(root);
    evb = evbuffer_new();
    evbuffer_add(evb, out, strlen(out));
    evhttp_send_reply(request_t->request, errcode, message, evb);
    if (evb)
        evbuffer_free(evb);
    free(message);
    free(out);
    va_end(args);
    cJSON_Delete(root);

}