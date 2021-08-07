#include <wangyonglin/linux.h>
#include <wangyonglin/wangyonglin.h>
#include <https/https.h>
#include <https/retsult.h>
#include <https/callback.h>
#include <https/openssl.h>
#include <event2/bufferevent_ssl.h>
#define MYHTTPD_SIGNATURE "wangyonglin v0.1"
void *https__dispatch(void *args);
static struct bufferevent *https__bufferevent_cb(struct event_base *base, void *arg);
int https__socket_create(configify_t *config, wangyonglin_https_t *https_t);
//static void login_cb(struct evhttp_request *req, void *arg);
static wangyonglin_https_t *wangyonglin_config_initialization(configify_t *config);
wangyonglin_https_t *wangyonglin_config_initialization(configify_t *config)
{
    //配置 HTTPS 需要的参数
    wangyonglin_https_t *https_t = (wangyonglin_https_t *)calloc(1, sizeof(wangyonglin_https_t));
    // 2. Traverse to a table.
    wangyonglin_conf_table_t *https = wangyonglin_conf_table_in(config->boot, "HTTPS");
    if (!https)
    {
        logify_printf(config, LOG_ERR, "missing [https]");
        return NULL;
    }

    // 3. Extract values
    wangyonglin_conf_datum_t port = wangyonglin_conf_int_in(https, "port");
    if (!port.ok)
    {
        logify_printf(config, LOG_ERR, "cannot read https.host", "");
        return NULL;
    }

    // 3. Extract values
    wangyonglin_conf_datum_t backlog = wangyonglin_conf_int_in(https, "backlog");
    if (!backlog.ok)
    {
        logify_printf(config, LOG_ERR, "cannot read https.backlog", "");
        return NULL;
    }

    // 3. Extract values
    wangyonglin_conf_datum_t threads = wangyonglin_conf_int_in(https, "threads");
    if (!threads.ok)
    {
        logify_printf(config, LOG_ERR, "cannot read https.threads", "");
        return NULL;
    }

    // 3. Extract values
    wangyonglin_conf_datum_t certificate_chain = wangyonglin_conf_string_in(https, "certificate_chain");
    if (!certificate_chain.ok)
    {
        logify_printf(config, LOG_ERR, "cannot read https.certificate_chain", "");
        return NULL;
    }

    // 3. Extract values
    wangyonglin_conf_datum_t private_key = wangyonglin_conf_string_in(https, "private_key");
    if (!private_key.ok)
    {
        logify_printf(config, LOG_ERR, "cannot read https.private_key", "");
        return NULL;
    }
    wangyonglin_string_setting(&https_t->private_key, private_key.u.s);
    wangyonglin_string_setting(&https_t->certificate_chain, certificate_chain.u.s);
    https_t->threads = threads.u.i;
    https_t->backlog = backlog.u.i;
    https_t->port = port.u.i;
    return https_t;
}
int https__application(configify_t *config,msgify_t *message)
{
    https__request_t request_t;
    request_t.config = config;
    request_t.message = message;
    //配置 HTTPS 需要的参数
    wangyonglin_https_t *https_t = wangyonglin_config_initialization(config);
    if (https_t == NULL)
    {
        exit(EXIT_FAILURE);
    }
    https_t->message = message;
    /* 选择服务器证书 和 服务器私钥. 1/2 创建SSL上下文环境 ，可以理解为 SSL句柄 */
    https_t->ctx = https__openssl_create(config);
    /* 选择服务器证书 和 服务器私钥. 2/2  设置服务器证书 和 服务器私钥 到 OPENSSL ctx上下文句柄中 */
    https__openssl_set(config, https_t->ctx, https_t->certificate_chain.data, https_t->private_key.data);
    /* 配置 SOCKET */
    sockify_t *socket_t = sockify_tcp(config, https_t->port, https_t->backlog);
    if (socket_t == NULL)
    {
        logify_printf(config, LOG_ERR, "Couldn't create an socket: exiting");
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
            logify_printf(config, LOG_ERR, "Couldn't create an event_base: exiting");
            return -8;
        }
        pinfo->httpd = evhttp_new(pinfo->base);
        if (pinfo->httpd == NULL)
        {
            logify_printf(config, LOG_ERR, "couldn't create evhttp. exiting.");
            return -9;
        }
        /* 
        使我们创建好的evhttp句柄 支持 SSL加密
        实际上，加密的动作和解密的动作都已经帮
        我们自动完成，我们拿到的数据就已经解密之后的
            */
        evhttp_set_bevcb(pinfo->httpd, https__bufferevent_cb, https_t->ctx);
        evhttp_set_cb(pinfo->httpd, "/wangyonglin/rf433/get", https__uri_wangyonglin_rf433, &request_t);
        evhttp_set_cb(pinfo->httpd, "/wangyonglin/trun/get", https__uri_wangyonglin_trun, &request_t);
        evhttp_set_gencb(pinfo->httpd, https__uri_notfound, config);
        /* 设置监听IP和端口 */
        if (evhttp_accept_socket(pinfo->httpd, socket_t->sockfd) != 0)
        {
            logify_printf(config, LOG_ERR, "evhttp_accept_socket failed! port:%d\n", socket_t->__hostshort);
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

void https_add_cjson(https__request_t *request_t, const char *topic, const char *data, char *out)
{

    /* 输出 JSON*/
    cJSON *root = cJSON_CreateObject(); //创建一个对象
    if (!root)
    {
        https__failure(request_t,"cJSON_CreateObject filt");
        return;
    }

    cJSON *result = cJSON_CreateObject();
    if (!result)
    {
        https__failure(request_t,"cJSON_CreateObject filt");
        return;
    }
    cJSON_AddTrueToObject(root, "success");
    cJSON_AddStringToObject(root, "message", "ok");
    cJSON_AddStringToObject(result, topic, data);
    cJSON_AddItemToObject(root, "result", result);
    char *res = cJSON_Print(root);
    bzero(out, sizeof(out));
    strcpy(out, res);
    cJSON_Delete(root);
    free(res);
}
void https_successify(https__request_t *request_t, char *result, size_t datlen)
{
    evhttp_add_header(request_t->request->output_headers, "Content-Type", "application/json;charset=UTF-8");
    evhttp_add_header(request_t->request->output_headers, "Connection", "keep-alive");
    struct evbuffer *evb = NULL;
    evb = evbuffer_new();
    evbuffer_add(evb, result, datlen);
    evhttp_send_reply(request_t->request, 200, "ok", evb);
    if (evb)
        evbuffer_free(evb);
}

void https__failure(https__request_t *request_t,const char *format, ...)
{
    struct evhttp_request *request = request_t->request;
    evhttp_add_header(request->output_headers, "Content-Type", "application/json;charset=UTF-8");
    evhttp_add_header(request->output_headers, "Connection", "keep-alive");
    va_list args;
    va_start(args, format);
    char *message = (char *)calloc(1, 512);
    sprintf(message, format, args);
    struct evbuffer *evb = NULL;
    /* 输出 JSON*/
    cJSON *root = cJSON_CreateObject(); //创建一个对象
    if (!root)
        return;

    cJSON_AddFalseToObject(root, "success");
    cJSON_AddStringToObject(root, "message", message);
    cJSON_AddNullToObject(root, "result");
    char *out = cJSON_Print(root);
    evb = evbuffer_new();
    evbuffer_add(evb, out, strlen(out));
    evhttp_send_reply(request_t->request, 500, message, evb);
    if (evb)
        evbuffer_free(evb);
    free(message);
    free(out);
    va_end(args);
    cJSON_Delete(root);
}