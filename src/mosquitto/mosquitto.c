#include <wangyonglin/linux.h>
#include <wangyonglin/wangyonglin.h>

#include <mosquitto/connect.h>
#include <mosquitto/message.h>
#include <mosquitto/subscribe.h>
#include <mosquitto/disconnect.h>
struct mosquitto *handler;

wangyonglin_mosquitto_t *wangyonglin_config_initialization(configify_t *config);

void *callback_mosquitto_task(void *arg)
{
    wangyonglin_mosquitto_t *mosquitto_t = (wangyonglin_mosquitto_t *)arg;
    configify_t *config = mosquitto_t->config;
    int msglen = mosquitto_t->msg_max_size;
    int ret;

    char buff[msglen];

    //初始化libmosquitto库
    ret = mosquitto_lib_init();
    if (ret)
    {
       logify_printf(config, LOG_ERR, "mosquitto lib init fail");
        pthread_exit(NULL);
    }
    //创建一个发布端实例
    handler = mosquitto_new("wangyonglin", true, mosquitto_t);
    if (handler == NULL)
    {

        logify_printf(config, LOG_ERR, "mosquitto new: %s", strerror(errno));
        mosquitto_lib_cleanup();
        pthread_exit(NULL);
    }

    ret = mosquitto_username_pw_set(handler, mosquitto_t->username.data, mosquitto_t->password.data);
    if (ret == MOSQ_ERR_INVAL)
    {
        logify_printf(config, LOG_ERR, "mosquitto username or password");
        mosquitto_lib_cleanup();
        pthread_exit(NULL);
    }

    else if (ret == MOSQ_ERR_NOMEM)
    {
        logify_printf(config, LOG_ERR, "mosquitto username or password memory condition occurred");
        mosquitto_lib_cleanup();
        pthread_exit(NULL);
    }

    //设置回调函数
    mosquitto_connect_callback_set(handler, connect__callback);
    mosquitto_disconnect_callback_set(handler, disconnect__callback);
    mosquitto_subscribe_callback_set(handler, subscribe__callback);
    mosquitto_message_callback_set(handler, message__callback);

    // 连接至服务器
    // 参数：句柄、ip（host）、端口、心跳
    ret = mosquitto_connect(handler, mosquitto_t->host.data, mosquitto_t->port, mosquitto_t->keep_alive);

    if (ret == MOSQ_ERR_INVAL)
    {
        logify_printf(config, LOG_ERR, "mosquitto connect parameters invalid");
        mosquitto_destroy(handler);
        mosquitto_lib_cleanup();
        pthread_exit(NULL);
    }
    else if (ret == MOSQ_ERR_ERRNO)
    {
        logify_printf(config, LOG_ERR, "mosquitto connect parameters %s", strerror(errno));
        mosquitto_destroy(handler);
        mosquitto_lib_cleanup();
        pthread_exit(NULL);
    }

    int loop = mosquitto_loop_start(handler);
    if (loop != MOSQ_ERR_SUCCESS)
    {
        if (loop == MOSQ_ERR_INVAL)
        {
            logify_printf(config, LOG_ERR, "mosquitto loop start if the input parameters were invalid");
        }
        else if (loop == MOSQ_ERR_NOT_SUPPORTED)
        {
            logify_printf(config, LOG_ERR, "mosquitto loop start if thread support is not available");
        }

        mosquitto_lib_cleanup();
        pthread_exit(NULL);
    }
    for (;;)
        ;
}

int mosquitto__appcation(configify_t *config, msgify_t *message)
{

    wangyonglin_mosquitto_t *mosquitto_t = wangyonglin_config_initialization(config);
    mosquitto_t->config=config;
    mosquitto_t->message=message;
    if (mosquitto_t == NULL)
    {
        logify_printf(config, LOG_ERR, "wangyonglin_config_initialization return NULL");
        return 0;
    }
    pthread_t pid;
    pthread_create(&pid, NULL, callback_mosquitto_task, mosquitto_t);

    return 0;
}
int mosquitto__publist(configify_t *config, const char *topic, char *payload, int payloadlen)
{
    if (handler != NULL)
    {
        int rc;
        rc = mosquitto_publish(handler, NULL, topic, payloadlen, payload, 0, 0);
        switch (rc)
        {
        case MOSQ_ERR_SUCCESS:
            logify_printf(config, LOG_INFO, "topic:%s on success", topic, payload);
            break;
        case MOSQ_ERR_INVAL:
            logify_printf(config, LOG_INFO, "mosquitto_publish() topic %s ->  if the input parameters were invalid.", topic);
            break;
        case MOSQ_ERR_NOMEM:
            logify_printf(config, LOG_INFO, "mosquitto_publish() topic %s -> if an out of memory condition occurred.", topic);
            break;
        case MOSQ_ERR_NO_CONN:
            logify_printf(config, LOG_INFO, "mosquitto_publish() topic %s ->  if the client isn't connected to a broker.", topic);
            break;
        case MOSQ_ERR_PROTOCOL:
            logify_printf(config, LOG_INFO, "mosquitto_publish() topic %s ->  if there is a protocol error communicating with the broker.", topic);
            break;
        case MOSQ_ERR_PAYLOAD_SIZE:
            logify_printf(config, LOG_INFO, "mosquitto_publish() topic %s ->  if payloadlen is too large.", topic);
            break;
        case MOSQ_ERR_MALFORMED_UTF8:
            logify_printf(config, LOG_INFO, "mosquitto_publish() topic %s ->  if the topic is not valid UTF-8.", topic);
            break;
        case MOSQ_ERR_DUPLICATE_PROPERTY:
            logify_printf(config, LOG_INFO, "mosquitto_publish() topic %s ->  if a property is duplicated where it is forbidden.", topic);
            break;
        case MOSQ_ERR_QOS_NOT_SUPPORTED:
            logify_printf(config, LOG_INFO, "mosquitto_publish() topic %s ->  if the QoS is greater than that supported by the broker.", topic);
            break;
        case MOSQ_ERR_OVERSIZE_PACKET:
            logify_printf(config, LOG_INFO, "mosquitto_publish() topic %s -> if the resulting packet would be larger than supported by the broker.", topic);
            break;
        default:
            logify_printf(config, LOG_INFO, "mosquitto_publish() topic %s ->  其它错误", topic);
            break;
        }
        return rc;
    }
}

wangyonglin_mosquitto_t *wangyonglin_config_initialization(configify_t *config)
{
    wangyonglin_mosquitto_t *mosquitto_t = (wangyonglin_mosquitto_t *)calloc(1, sizeof(wangyonglin_mosquitto_t));

    wangyonglin_conf_table_t *mosquitto = wangyonglin_conf_table_in(config->boot, "MOSQUITTO");
    if (!mosquitto)
    {
        logify_printf(config, LOG_ERR, "missing [mosquitto]", "");
        return NULL;
    }
    // 3. Extract values
    wangyonglin_conf_datum_t username = wangyonglin_conf_string_in(mosquitto, "username");
    if (!username.ok)
    {
        logify_printf(config, LOG_ERR, "cannot read mosquitto.username", "");
        return NULL;
    }

    // 3. Extract values
    wangyonglin_conf_datum_t password = wangyonglin_conf_string_in(mosquitto, "password");
    if (!password.ok)
    {
        logify_printf(config, LOG_ERR, "cannot read mosquitto.password", "");
        return NULL;
    }

    // 3. Extract values
    wangyonglin_conf_datum_t host = wangyonglin_conf_string_in(mosquitto, "host");
    if (!host.ok)
    {
        logify_printf(config, LOG_ERR, "cannot read mosquitto.host", "");
        return NULL;
    }

    wangyonglin_conf_datum_t port = wangyonglin_conf_int_in(mosquitto, "port");
    if (!port.ok)
    {
        logify_printf(config, LOG_ERR, "cannot read mosquitto.port", "");
        return NULL;
    }

    wangyonglin_conf_datum_t keep_alive = wangyonglin_conf_int_in(mosquitto, "keep_alive");
    if (!keep_alive.ok)
    {
        logify_printf(config, LOG_ERR, "cannot read mosquitto.keep_alive", "");
        return NULL;
    }

    wangyonglin_conf_datum_t msg_max_size = wangyonglin_conf_int_in(mosquitto, "msg_max_size");
    if (!msg_max_size.ok)
    {
        logify_printf(config, LOG_ERR, "cannot read mosquitto.msg_max_size", "");
        return NULL;
    }

    wangyonglin_string_setting(&mosquitto_t->username, username.u.s);
    wangyonglin_string_setting(&mosquitto_t->password, password.u.s);
    wangyonglin_string_setting(&mosquitto_t->host, host.u.s);

    mosquitto_t->port = port.u.i;
    mosquitto_t->keep_alive = keep_alive.u.i;
    mosquitto_t->msg_max_size = msg_max_size.u.i;
    mosquitto_t->config = config;
    return mosquitto_t;
}
