#ifndef INCLUDE_WANGYONGLIN_PID_H
#define INCLUDE_WANGYONGLIN_PID_H
#include <wangyonglin/linux.h>
#include <wangyonglin/wangyonglin.h>

int pid__create(struct wangyonglin__config *config);
void pid__remove(struct wangyonglin__config *config);
int pid__test(struct wangyonglin__config *config);
#endif
