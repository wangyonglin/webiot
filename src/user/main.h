#ifndef _WANGYONGLIN_USER_H_INCLUDE_
#define _WANGYONGLIN_USER_H_INCLUDE_
#include <wangyonglin/config.h>
#include <wangyonglin/core.h>

typedef struct
{
    cJSON *root;
    cJSON *topic;
    cJSON *payload;
} wangyonglin_mqtt_t;

int matt_json_parse(wangyonglin_mqtt_t *mqtt_t, char *str);
#endif