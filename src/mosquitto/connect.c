#include <wangyonglin/linux.h>
#include <wangyonglin/wangyonglin.h>
#include <mosquitto/connect.h>

void connect__callback(struct mosquitto *mosq, void *obj, int rc)
{
    wangyonglin_mosquitto_t *mosquitto_t = (wangyonglin_mosquitto_t *)obj;
    configify_t *config = mosquitto_t->config;
    logify_printf(config, LOG_INFO, "Call the function: on_connect");

    if (rc)
    {
        // 连接错误，退出程序
        logify_printf(config, LOG_INFO, "on_connect error!");
      
    }

}