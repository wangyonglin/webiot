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

int wangyonglin_conf_init(const char *ininame);
int wangyonglin_conf_get(void *dest, const char *key, wangyonglin_type_t type);
#endif /**_WANGYONGLIN_CONF_H_INCLUDE_**/