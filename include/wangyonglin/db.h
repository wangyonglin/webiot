#ifndef _DB_H_INCLUDE_
#define _DB_H_INCLUDE_
#include <wangyonglin/linux_config.h>
#include <wangyonglin/wangyonglin.h>
typedef struct wangyonglin__db wangyonglin__db_t;

struct wangyonglin__db
{
    wangyonglin_signal_t signal_t;
    time_t now_s;      /* Monotonic clock, where possible */
    time_t now_real_s; /* Read clock, for measuring session/message expiry */
    wangyonglin__config_t *config;
};

#endif