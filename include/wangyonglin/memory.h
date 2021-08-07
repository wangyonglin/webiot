#ifndef INCLUDE_WANGYONGLIN_MEMORY_H
#define INCLUDE_WANGYONGLIN_MEMORY_H
#include <wangyonglin/linux.h>
#include <wangyonglin/wangyonglin.h>
#define memify_memset memset
#define memify_malloc malloc
#define memify_free free
#define memify_calloc calloc
#endif