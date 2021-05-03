#ifndef INCLUDE_WANGYONGLIN_MEMORY_H
#define INCLUDE_WANGYONGLIN_MEMORY_H
#include <wangyonglin/linux.h>
#include <wangyonglin/wangyonglin.h>

void *wangyonglin__calloc(size_t nmemb, size_t size);
void wangyonglin__free(void *mem);
void *wangyonglin__malloc(size_t size);
#endif