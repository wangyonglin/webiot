#ifndef _WANGYONGLIN_CONF_H_INCLUDE_
#define _WANGYONGLIN_CONF_H_INCLUDE_
#include <wangyonglin/config.h>
#include <wangyonglin/core.h>



int wangyonglin_conf_setting(const char *filename);
wangyonglin_string_t wangyonglin_conf_string(const char *lc_key);
int wangyonglin_conf_int(const char *lc_key, int notfound);
#endif /**_WANGYONGLIN_CONF_H_INCLUDE_**/