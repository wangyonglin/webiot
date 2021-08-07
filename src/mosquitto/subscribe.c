#include <wangyonglin/linux.h>
#include <wangyonglin/wangyonglin.h>
#include <mosquitto/subscribe.h>
void subscribe__callback(struct mosquitto *mosq, void *obj, int mid, int qos_count, const int *granted_qos)
{
    wangyonglin_mosquitto_t *mosquitto_t = (wangyonglin_mosquitto_t *)obj;
    configify_t *config = mosquitto_t->config;
    logify_printf(config, LOG_INFO, "Call the function: on_subscribe");
}