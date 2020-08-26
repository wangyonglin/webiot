#ifndef _WANGYONGLIN_TIME_H_INCLUDE_
#define _WANGYONGLIN_TIME_H_INCLUDE_

#include <wangyonglin/config.h>
#include <wangyonglin/core.h>

struct wangyonglin_time_s
{
    struct tm *t;
	struct timeval *tv;
};
  struct tm * wangyonglin_time_now();
#endif /**_WANGYONGLIN_TIME_H_INCLUDE_**/
