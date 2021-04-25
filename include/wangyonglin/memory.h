#ifndef _WANGYONGLIN_MEMORY_H_INCLUDE_
#define _WANGYONGLIN_MEMORY_H_INCLUDE_
#include <wangyonglin/linux_config.h>
#include <wangyonglin/wangyonglin.h>

void *wangyonglin__calloc(size_t nmemb, size_t size);
void wangyonglin__free(void *mem);
void *wangyonglin__malloc(size_t size);
#endif