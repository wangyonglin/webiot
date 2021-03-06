#include <wangyonglin/config.h>
#include <wangyonglin/core.h>
#include <mosquitto.h>

#include <mosquitto/mosquitto.h>
wangyonglin_mosquitto_t mosquitto_t;

wangyonglin_mosquitto_conf_t conf_t;
wangyonglin_mosquitto_user_t user_t;
struct mosquitto *handler;
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
    wangyonglin_mosquitto_conf_t *conf_t = mosquitto_t->conf_t;
    wangyonglin_mosquitto_user_t *user_t = mosquitto_t->user_t;
    int msglen = conf_t->msg_max_size;
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
    ret = mosquitto_username_pw_set(handler, user_t->username.data, user_t->password.data);
    if (ret == MOSQ_ERR_INVAL)
    {
        wangyonglin_logger_failure("mosquitto username or password");
        pthread_exit(NULL);
    }

    else if (ret == MOSQ_ERR_NOMEM)
    {
        wangyonglin_logger_failure("mosquitto username or password memory condition occurred");
        pthread_exit(NULL);
    }

    //设置回调函数
    mosquitto_connect_callback_set(handler, wangyonglin_connect_callback);
    mosquitto_disconnect_callback_set(handler, wangyonglin_disconnect_callback);
    mosquitto_publish_callback_set(handler, wangyonglin_publish_callback);

    // 连接至服务器
    // 参数：句柄、ip（host）、端口、心跳
    ret = mosquitto_connect(handler, conf_t->host.data, conf_t->port, conf_t->keep_alive);
    wangyonglin_logger_success("\t username :%s \r\n", user_t->username.data);
    wangyonglin_logger_success("\t password :%s \r\n", user_t->password.data);
    wangyonglin_logger_success("\t host :%d \r\n", conf_t->host.data);
    wangyonglin_logger_success("\t port :%d \r\n", conf_t->port);
    wangyonglin_logger_success("\t keep_alive :%d \r\n", conf_t->keep_alive);
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

int wangyonglin_mosquitto_appcation(wangyonglin_signal_t *signal_t)
{

    conf_t.host = wangyonglin_conf_string("mosquitto_host");
    conf_t.port = wangyonglin_conf_int("mosquitto_port", 1883);
    conf_t.keep_alive = wangyonglin_conf_int("mosquitto_keep_alive", 60);
    conf_t.msg_max_size = wangyonglin_conf_int("mosquitto_msg_max_size", 512);
    user_t.username = wangyonglin_conf_string("mosquitto_username");
    user_t.password = wangyonglin_conf_string("mosquitto_password");
    mosquitto_t.signal_t = signal_t;
    mosquitto_t.conf_t = &conf_t;
    mosquitto_t.user_t = &user_t;
    pthread_t pid;
    pthread_create(&pid, NULL, callback_mosquitto_task, &mosquitto_t);

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