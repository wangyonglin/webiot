#ifndef _MOSQUITTO_SERVER_H_INCLUDE_
#define _MOSQUITTO_SERVER_H_INCLUDE_
#include <wangyonglin/config.h>
#include <wangyonglin/core.h>

#include <mosquitto/conf.h>
typedef struct wangyonglin_mosquitto_s wangyonglin_mosquitto_t;
typedef struct wangyonglin_mosquitto_conf_s wangyonglin_mosquitto_conf_t;

struct wangyonglin_mosquitto_s
{
    wangyonglin_mosquitto_conf_t *conf;
    wangyonglin_signal_t * signal_t;
    struct mosquitto *mosq;
};
void wangyonglin_mosquitto_create(wangyonglin_mosquitto_t *mosquitto_t);
void wangyonglin_mosquitto_init(wangyonglin_mosquitto_t *mosquitto_t, wangyonglin_signal_t *signal_t);
#endif