#ifndef _WANGYONGLIN_CONF_H_INCLUDE_
#define _WANGYONGLIN_CONF_H_INCLUDE_
#include <wangyonglin/config.h>
#include <wangyonglin/core.h>

typedef enum wangyonglin_type_e
{
    wangyonglin_type_string,
    wangyonglin_type_int,
    wangyonglin_type_bool
} wangyonglin_type_t;

typedef enum wangyonglin_conf_e wangyonglin_conf_t;

enum wangyonglin_conf_e
{
    wangyonglin_conf_string,
    wangyonglin_conf_int,
    wangyonglin_conf_bool
};

int wangyonglin_conf_init(const char *ininame);
int wangyonglin_conf_get(void *dest, const char *key, wangyonglin_type_t type);
#endif /**_WANGYONGLIN_CONF_H_INCLUDE_**/