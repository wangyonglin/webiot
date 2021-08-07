#ifndef INCLUDE_WANGYONGLIN_PID_H
#define INCLUDE_WANGYONGLIN_PID_H
#include <wangyonglin/linux.h>
#include <wangyonglin/wangyonglin.h>

int pidify_create(struct wangyonglin__config *config);
void pidify_remove(struct wangyonglin__config *config);
int pidify_test(struct wangyonglin__config *config);
#endif
