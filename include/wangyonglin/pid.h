#ifndef INCLUDE_WANGYONGLIN_PID_H
#define INCLUDE_WANGYONGLIN_PID_H
#include <wangyonglin/linux.h>
#include <wangyonglin/wangyonglin.h>

int wangyonglin__pid_create(struct wangyonglin__config *config);
void wangyonglin__pid_remove(struct wangyonglin__config *config);
int wangyonglin__pid_test(struct wangyonglin__config *config);
#endif
