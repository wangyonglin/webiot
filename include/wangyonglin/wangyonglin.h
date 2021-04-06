#ifndef _WANGYONGLIN_WANGYONGLIN_H_INCLUDE_
#define _WANGYONGLIN_WANGYONGLIN_H_INCLUDE_
#include <wangyonglin/config.h>
#include <wangyonglin/core.h>
wangyonglin_conf_table_t * wangyonglin_application_initialization(const char * file,int daemon);
struct tm *wangyonglin_core_localtime();

#endif /**_WANGYONGLIN_WANGYONGLIN_H_INCLUDE_**/
