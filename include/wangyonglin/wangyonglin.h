#ifndef _WANGYONGLIN_WANGYONGLIN_H_INCLUDE_
#define _WANGYONGLIN_WANGYONGLIN_H_INCLUDE_
#include <wangyonglin/config.h>
#include <wangyonglin/core.h>
int wangyonglin_system_init(const char * filename,int daemon);
struct tm *wangyonglin_core_localtime();

#endif /**_WANGYONGLIN_WANGYONGLIN_H_INCLUDE_**/
