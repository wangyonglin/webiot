#ifndef INCLUDE_WANGYONGLIN_ERROR_H
#define INCLUDE_WANGYONGLIN_ERROR_H
#include <wangyonglin/linux.h>
#include <wangyonglin/wangyonglin.h>


void wangyonglin_error_perror(const char *__format, ...);
void wangyonglin_error_exit(int __status, const char *__format, ...);
#endif 