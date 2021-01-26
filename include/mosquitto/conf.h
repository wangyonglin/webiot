#ifndef _WANGYONGLIN_MQSQUITTO_CONF_H_INCLUDE_
#define _WANGYONGLIN_MQSQUITTO_CONF_H_INCLUDE_
#include <wangyonglin/config.h>
#include <wangyonglin/core.h>

typedef struct wangyonglin_mosquitto_conf_s wangyonglin_mosquitto_conf_t;

struct wangyonglin_mosquitto_conf_s
{
    char host[16];
    int port;
    int keep_alive;
    int msg_max_size;
};

int wangyonglin_mosquitto_conf_init(wangyonglin_mosquitto_conf_t *mosquitto_conf_t);
#endif