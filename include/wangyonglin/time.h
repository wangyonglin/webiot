#ifndef INCLUDE_WANGYONGLIN_TIME_H
#define INCLUDE_WANGYONGLIN_TIME_H
#include <wangyonglin/linux.h>
#include <wangyonglin/wangyonglin.h>

time_t wangyonglin__time(void);
int time__timestamp(struct wangyonglin__config *config, char *strout,int sizeout);
#endif 
