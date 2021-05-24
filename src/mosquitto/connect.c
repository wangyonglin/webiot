#include <wangyonglin/linux.h>
#include <wangyonglin/wangyonglin.h>
#include <mosquitto/connect.h>

void connect__callback(struct mosquitto *mosq, void *obj, int rc)
{
    wangyonglin_mosquitto_t *mosquitto_t = (wangyonglin_mosquitto_t *)obj;
    struct wangyonglin__config *config = mosquitto_t->config;
    wangyonglin__logger(config, LOG_INFO, "Call the function: on_connect");

    if (rc)
    {
        // 连接错误，退出程序
        wangyonglin__logger(config, LOG_INFO, "on_connect error!");
        exit(1);
    }
    else
    {
        // 订阅主题
        // 参数：句柄、id、订阅的主题、qos
        if (mosquitto_subscribe(mosq, NULL, "jscs", 2))
        {
            wangyonglin__logger(config, LOG_INFO, "subscribe topic error: jscs");
            exit(1);
        }
    }
}