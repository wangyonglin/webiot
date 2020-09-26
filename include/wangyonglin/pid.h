#ifndef _WANGYONGLIN_PID_H_INCLUDE_
#define _WANGYONGLIN_PID_H_INCLUDE_
#include <wangyonglin/config.h>
#include <wangyonglin/core.h>
typedef struct wangyonglin_pid_s
{
    char name[128];
} wangyonglin_pid_t;
int wangyonglin_pid_init(wangyonglin_pid_t *pid);
void wangyonglin_pid_conf(wangyonglin_pid_t *pid);
#endif /**_WANGYONGLIN_PID_H_INCLUDE_**/
