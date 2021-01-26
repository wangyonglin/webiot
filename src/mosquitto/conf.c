#include <wangyonglin/config.h>
#include <wangyonglin/core.h>

#include <mosquitto/conf.h>

int wangyonglin_mosquitto_conf_init(wangyonglin_mosquitto_conf_t *conf)
{
    wangyonglin_conf_string(conf->host, "mosquitto:host");
    conf->port = wangyonglin_conf_number("mosquitto:port");
    conf->keep_alive = wangyonglin_conf_number("mosquitto:keep_alive");
    conf->msg_max_size = wangyonglin_conf_number("mosquitto:msg_max_size");
    return 0;
}