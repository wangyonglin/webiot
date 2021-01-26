#ifndef _MOSQUITTO_SERVER_H_INCLUDE_
#define _MOSQUITTO_SERVER_H_INCLUDE_
#include <wangyonglin/config.h>
#include <wangyonglin/core.h>

#include <mosquitto/conf.h>
typedef struct wangyonglin_mosquitto_s wangyonglin_mosquitto_t;
typedef struct wangyonglin_mosquitto_conf_s wangyonglin_mosquitto_conf_t;

struct wangyonglin_mosquitto_s
{
   
    wangyonglin_mosquitto_conf_t * conf;
};
void wangyonglin_mosquitto_start();
#endif