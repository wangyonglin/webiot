#ifndef INCLUDE_WANGYONGLIN_PID_H
#define INCLUDE_WANGYONGLIN_PID_H
#include <wangyonglin/linux.h>
#include <wangyonglin/wangyonglin.h>

int pidify_create(configify_t *config);
void pidify_remove(configify_t *config);
int pidify_test(configify_t *config);
#endif
