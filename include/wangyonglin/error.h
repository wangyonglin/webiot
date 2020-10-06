#ifndef _WANGYONGLIN_ERROR_H_INCLUDE_
#define _WANGYONGLIN_ERROR_H_INCLUDE_
#include <wangyonglin/config.h>
#include <wangyonglin/core.h>
void wangyonglin_error_perror(const char *__format, ...);
void wangyonglin_error_exit(int __status, const char *__format, ...);
#endif /**_WANGYONGLIN_LIB_H_INCLUDE_**/