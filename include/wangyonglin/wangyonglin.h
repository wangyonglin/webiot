#ifndef _WANGYONGLIN_WANGYONGLIN_H_INCLUDE_
#define _WANGYONGLIN_WANGYONGLIN_H_INCLUDE_
#include <wangyonglin/config.h>
#include <wangyonglin/core.h>

typedef struct wangyonglin_core_s wangyonglin_core_t;

struct wangyonglin_core_s
{
   
};

wangyonglin_core_t * wangyonglin(int argc, char *argv[]);
struct tm * wangyonglin_core_localtime();

#endif /**_WANGYONGLIN_WANGYONGLIN_H_INCLUDE_**/
