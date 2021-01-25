#ifndef _WANGYONGLIN_CONF_H_INCLUDE_
#define _WANGYONGLIN_CONF_H_INCLUDE_
#include <wangyonglin/config.h>
#include <wangyonglin/core.h>

int wangyonglin_conf_init(const char *ininame);

char *wangyonglin_conf_string(char * dest,const char *key);
int wangyonglin_conf_number(const char *key);
#endif /**_WANGYONGLIN_CONF_H_INCLUDE_**/