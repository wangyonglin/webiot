#ifndef _WANGYONGLIN_LOG_H_INCLUDE_
#define _WANGYONGLIN_LOG_H_INCLUDE_

#include <wangyonglin/config.h>
#include <wangyonglin/core.h>


typedef enum {
	LOG_INFO,LOG_DEBUG,LOG_WARN,LOG_ERROR,LOG_EMERG
}wangyonglin_log_levels_t;

struct wangyonglin_log_s{
	char  error_log[128];
	char  access_log[128];
};

int  wangyonglin_log_init(wangyonglin_log_t * log);
void wangyonglin_log_info(const char *fmt, ...);
void wangyonglin_log_error(wangyonglin_uint_t level,const char *fmt, ...);


#endif /**_WANGYONGLIN_LOG_H_INCLUDE_**/
