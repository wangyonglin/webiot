#include <wangyonglin/linux.h>
#include <wangyonglin/wangyonglin.h>
#include <mosquitto/message.h>

void message__callback(struct mosquitto *mosq, void *obj, const struct mosquitto_message *msg)
{
    wangyonglin_mosquitto_t *mosquitto_t = (wangyonglin_mosquitto_t *)obj;
    configify_t *config = mosquitto_t->config;
    logify_printf(config, LOG_INFO, "Call the function: on_message");
    logify_printf(config, LOG_INFO, "Recieve a message of %s : %s", (char *)msg->topic, (char *)msg->payload);

    if (0 == strcmp(msg->payload, "quit"))
    {
        mosquitto_disconnect(mosq);
    }
}