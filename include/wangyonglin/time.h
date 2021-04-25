#ifndef _WANGYONGLIN_TIME_H_INCLUDE_
#define _WANGYONGLIN_TIME_H_INCLUDE_
#include <wangyonglin/linux_config.h>
#include <wangyonglin/wangyonglin.h>

time_t wangyonglin__time(void);
int time__timestamp(struct wangyonglin__config *config, char *strout,int sizeout);
#endif 
