#include <wangyonglin/config.h>
#include <wangyonglin/core.h>
#include <mosquitto.h>
#include <mosquitto/conf.h>
#include <mosquitto/service.h>
wangyonglin_mosquitto_conf_t conf;
void wangyonglin_connect_callback(struct mosquitto *mosq, void *obj, int rc)
{
    printf("Call the function: my_connect_callback\n");
}

void wangyonglin_disconnect_callback(struct mosquitto *mosq, void *obj, int rc)
{
    printf("Call the function: my_disconnect_callback\n");
}

void wangyonglin_publish_callback(struct mosquitto *mosq, void *obj, int mid)
{
    printf("Call the function: my_publish_callback\n");
}
void *callback_mosquitto_task(void *arg)
{
    wangyonglin_mosquitto_t *mosquitto_t = (wangyonglin_mosquitto_t *)arg;
    wangyonglin_mosquitto_conf_t *conf = mosquitto_t->conf;
    fprintf(stdout, "\t callback_mosquitto_task host %s \n", conf->host);
    int msglen = conf->msg_max_size;
    int ret;
    struct mosquitto *mosq;
    char buff[msglen];

    //初始化libmosquitto库
    ret = mosquitto_lib_init();
    if (ret)
    {
        printf("Init lib error!\n");
    }
    //创建一个发布端实例
    mosquitto_t->mosq = mosquitto_new("wangyonglin", true, NULL);
    if (mosquitto_t->mosq == NULL)
    {
        printf("New pub_test error!\n");
        mosquitto_lib_cleanup();
        pthread_exit(NULL);
    }

    //设置回调函数
    mosquitto_connect_callback_set(mosquitto_t->mosq, wangyonglin_connect_callback);
    mosquitto_disconnect_callback_set(mosquitto_t->mosq, wangyonglin_disconnect_callback);
    mosquitto_publish_callback_set(mosquitto_t->mosq, wangyonglin_publish_callback);
    printf("New pub_test error %s !\n", conf->host);
    // 连接至服务器
    // 参数：句柄、ip（host）、端口、心跳
    ret = mosquitto_connect(mosquitto_t->mosq, conf->host, conf->port, conf->keep_alive);
    if (ret)
    {
        printf("Connect server error!\n");
        mosquitto_destroy(mosquitto_t->mosq);
        mosquitto_lib_cleanup();
        pthread_exit(NULL);
    }

    printf("Start!\n");
    int loop = mosquitto_loop_start(mosquitto_t->mosq);
    if (loop != MOSQ_ERR_SUCCESS)
    {
        printf("mosquitto loop error\n");
        pthread_exit(NULL);
    }
    for (;;);
}

void wangyonglin_mosquitto_create(wangyonglin_mosquitto_t *mosquitto_t)
{
    pthread_create(&mosquitto_t->pid, NULL, callback_mosquitto_task, mosquitto_t);
    //pthread_join(pid, NULL);
   // mosquitto_destroy(mosquitto_t->mosq);
   // mosquitto_lib_cleanup();
    printf("End!\n");
}
void wangyonglin_mosquitto_init(wangyonglin_mosquitto_t *mosquitto_t, wangyonglin_signal_t *signal_t)
{
    wangyonglin_mosquitto_conf_init(&conf);
    mosquitto_t->conf = &conf;
    mosquitto_t->signal_t = signal_t;
}