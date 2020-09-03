#ifndef _WANGYONGLIN_PID_H_INCLUDE_
#define _WANGYONGLIN_PID_H_INCLUDE_
#include <wangyonglin/config.h>
#include <wangyonglin/core.h>
struct wangyonglin_pid_s{
	char  filename[128];
};



int wangyonglin_pid_create(wangyonglin_pid_t * pid);

#endif /**_WANGYONGLIN_PID_H_INCLUDE_**/
