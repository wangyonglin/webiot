#ifndef _WANGYONGLIN_CORE_H_INCLUDE_
#define _WANGYONGLIN_CORE_H_INCLUDE_
#include <wangyonglin/linux_config.h>
#include <wangyonglin/wangyonglin.h>
int application(struct wangyonglin__config *config);
#ifndef WANGYONGLIN__CALL
#define WANGYONGLIN__CALL
typedef struct wangyonglin__call wangyonglin__call_t;
struct wangyonglin__call
{
    void *(*app)(struct wangyonglin__config *config, void *args);
    //struct wangyonglin__config *config;
};
#endif
#endif
