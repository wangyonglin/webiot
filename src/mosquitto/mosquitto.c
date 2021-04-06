#include <wangyonglin/config.h>
#include <wangyonglin/core.h>
#include <mosquitto.h>

#include <mosquitto/mosquitto.h>
 
struct mosquitto *handler;
wangyonglin_mosquitto_t *wangyonglin_config_initialization(wangyonglin_conf_table_t *conf);

void wangyonglin_connect_callback(struct mosquitto *mosq, void *obj, int rc)
{
    wangyonglin_logger_success("mosquitto connect ok");
}

void wangyonglin_disconnect_callback(struct mosquitto *mosq, void *obj, int rc)
{

    wangyonglin_logger_success("mosquitto disconnect ok");
}

void wangyonglin_publish_callback(struct mosquitto *mosq, void *obj, int mid)
{
    wangyonglin_logger_success("mosquitto publish ok");
}
void *callback_mosquitto_task(void *arg)
{
    wangyonglin_mosquitto_t *mosquitto_t = (wangyonglin_mosquitto_t *)arg;
    int msglen = mosquitto_t->msg_max_size;
    int ret;

    char buff[msglen];

    //初始化libmosquitto库
    ret = mosquitto_lib_init();
    if (ret)
    {
        printf("Init lib error!\n");
    }
    //创建一个发布端实例
    handler = mosquitto_new("wangyonglin", true, NULL);
    if (handler == NULL)
    {

        wangyonglin_logger_failure("mosquitto new: %s", strerror(errno));
        mosquitto_lib_cleanup();
        pthread_exit(NULL);
    }
    ret = mosquitto_username_pw_set(handler, mosquitto_t->username.data, mosquitto_t->password.data);
    if (ret == MOSQ_ERR_INVAL)
    {
        wangyonglin_logger_failure("mosquitto username or password");
        mosquitto_lib_cleanup();
        pthread_exit(NULL);
    }

    else if (ret == MOSQ_ERR_NOMEM)
    {
        wangyonglin_logger_failure("mosquitto username or password memory condition occurred");
        mosquitto_lib_cleanup();
        pthread_exit(NULL);
    }

    //设置回调函数
    mosquitto_connect_callback_set(handler, wangyonglin_connect_callback);
    mosquitto_disconnect_callback_set(handler, wangyonglin_disconnect_callback);
    mosquitto_publish_callback_set(handler, wangyonglin_publish_callback);

    // 连接至服务器
    // 参数：句柄、ip（host）、端口、心跳
    ret = mosquitto_connect(handler, mosquitto_t->host.data, mosquitto_t->port, mosquitto_t->keep_alive);

    if (ret == MOSQ_ERR_INVAL)
    {
        wangyonglin_logger_failure("mosquitto connect parameters invalid");
        mosquitto_destroy(handler);
        mosquitto_lib_cleanup();
        pthread_exit(NULL);
    }
    else if (ret == MOSQ_ERR_ERRNO)
    {
        wangyonglin_logger_failure("mosquitto connect parameters %s", strerror(errno));
        mosquitto_destroy(handler);
        mosquitto_lib_cleanup();
        pthread_exit(NULL);
    }

    int loop = mosquitto_loop_start(handler);
    if (loop != MOSQ_ERR_SUCCESS)
    {
        if (loop == MOSQ_ERR_INVAL)
        {
            wangyonglin_logger_failure("mosquitto loop start if the input parameters were invalid");
        }
        else if (loop == MOSQ_ERR_NOT_SUPPORTED)
        {
            wangyonglin_logger_failure("mosquitto loop start if thread support is not available");
        }

        mosquitto_lib_cleanup();
        pthread_exit(NULL);
    }
    for (;;)
        ;
}

int wangyonglin_mosquitto_appcation(wangyonglin_conf_table_t *conf, wangyonglin_signal_t *signal_t)
{

    wangyonglin_mosquitto_t *mosquitto_t = wangyonglin_config_initialization(conf);
    if (mosquitto_t == NULL)
    {
        wangyonglin_logger_failure("wangyonglin_config_initialization return NULL");
        return 0;
    }
    mosquitto_t->signal_t = signal_t;
    pthread_t pid;
    pthread_create(&pid, NULL, callback_mosquitto_task, mosquitto_t);

    printf("End!\n");
    return 0;
}
void wangyonglin_mosquitto_publist(const char *topic, char *payload, int payloadlen)
{
    if (handler != NULL)
    {
        int ret;
        ret = mosquitto_publish(handler, NULL, topic, payloadlen, payload, 0, 0);
        switch (ret)
        {
        case MOSQ_ERR_SUCCESS:
            wangyonglin_logger_success("\t topic:%s    payload:%s\r\n", topic, payload);
            break;
        case MOSQ_ERR_INVAL:
            wangyonglin_logger_failure("mosquitto_publish() topic %s ->  if the input parameters were invalid.", topic);
            break;
        default:
            wangyonglin_logger_failure("mosquitto_publish() topic %s ->  其它错误", topic);
            break;
        }
    }
}

wangyonglin_mosquitto_t *wangyonglin_config_initialization(wangyonglin_conf_table_t *conf)
{
    wangyonglin_mosquitto_t * mosquitto_t = (wangyonglin_mosquitto_t *)calloc(1, sizeof(wangyonglin_mosquitto_t));


    wangyonglin_conf_table_t *mosquitto = wangyonglin_conf_table_in(conf, "MOSQUITTO");
    if (!mosquitto)
    {
        wangyonglin_logger_failure("missing [mosquitto]", "");
        return NULL;
    }
    // 3. Extract values
    wangyonglin_conf_datum_t username = wangyonglin_conf_string_in(mosquitto, "username");
    if (!username.ok)
    {
        wangyonglin_logger_failure("cannot read mosquitto.username", "");
        return NULL;
    }
    printf(username.u.s);

    // 3. Extract values
    wangyonglin_conf_datum_t password = wangyonglin_conf_string_in(mosquitto, "password");
    if (!password.ok)
    {
        wangyonglin_logger_failure("cannot read mosquitto.password", "");
        return NULL;
    }

    // 3. Extract values
    wangyonglin_conf_datum_t host = wangyonglin_conf_string_in(mosquitto, "host");
    if (!host.ok)
    {
        wangyonglin_logger_failure("cannot read mosquitto.host", "");
        return NULL;
    }

    wangyonglin_conf_datum_t port = wangyonglin_conf_int_in(mosquitto, "port");
    if (!port.ok)
    {
        wangyonglin_logger_failure("cannot read mosquitto.port", "");
        return NULL;
    }

    wangyonglin_conf_datum_t keep_alive = wangyonglin_conf_int_in(mosquitto, "keep_alive");
    if (!keep_alive.ok)
    {
        wangyonglin_logger_failure("cannot read mosquitto.keep_alive", "");
        return NULL;
    }

    wangyonglin_conf_datum_t msg_max_size = wangyonglin_conf_int_in(mosquitto, "msg_max_size");
    if (!msg_max_size.ok)
    {
        wangyonglin_logger_failure("cannot read mosquitto.msg_max_size", "");
        return NULL;
    }
    printf("\tport%d\t\n", port.u.i);

    wangyonglin_string_setting(&mosquitto_t->username, username.u.s);
    wangyonglin_string_setting(&mosquitto_t->password, password.u.s);
    wangyonglin_string_setting(&mosquitto_t->host, host.u.s);

    mosquitto_t->port = port.u.i;
    mosquitto_t->keep_alive = keep_alive.u.i;
    mosquitto_t->msg_max_size = msg_max_size.u.i;
    return mosquitto_t;
}