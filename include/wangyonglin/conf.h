#ifndef _WANGYONGLIN_CONF_H_INCLUDE_
#define _WANGYONGLIN_CONF_H_INCLUDE_
#include <wangyonglin/config.h>
#include <wangyonglin/core.h>
#define wangyonglin_char_t char
struct wangyonglin_conf_s
{
     char filename[128];
     wangyonglin_pid_t * pid;
     wangyonglin_log_t * log;
};

extern wangyonglin_conf_t * conf;

int wangyonglin_conf_open(const char * filename);
void wangyonglin_conf_close();

char * wangyonglin_conf_read(const char *name);

#endif /**_WANGYONGLIN_CONF_H_INCLUDE_**/