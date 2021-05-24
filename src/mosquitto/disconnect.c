#include <wangyonglin/linux.h>
#include <wangyonglin/wangyonglin.h>
#include <mosquitto/disconnect.h>
void disconnect__callback(struct mosquitto *mosq, void *obj, int rc)
{
    wangyonglin_mosquitto_t *mosquitto_t = (wangyonglin_mosquitto_t *)obj;
    struct wangyonglin__config *config = mosquitto_t->config;
    wangyonglin__logger(config, LOG_INFO, "mosquitto disconnect ok");
}