#ifndef INCLUDE_WANGYONGLIN_TIME_H
#define INCLUDE_WANGYONGLIN_TIME_H
#include <wangyonglin/linux.h>
#include <wangyonglin/wangyonglin.h>

time_t timeify_time(void);
int timeify_timestamp(configify_t *config, char *strout,int sizeout);
#endif 
