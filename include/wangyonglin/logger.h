#ifndef _WANGYONGLIN_LOGGER_H_INCLUDE_
#define _WANGYONGLIN_LOGGER_H_INCLUDE_

#include <wangyonglin/config.h>
#include <wangyonglin/core.h>
typedef struct wangyonglin_logger_s wangyonglin_logger_t;

struct wangyonglin_logger_s
{
    wangyonglin_string_t alog;
    wangyonglin_string_t elog;
};
int wangyonglin_logger_init(wangyonglin_conf_table_t *conf);

void wangyonglin_logger_success(const char *format, ...);
void wangyonglin_logger_failure(const char *format, ...);

#endif /**_WANGYONGLIN_LOGGER_H_INCLUDE_**/
