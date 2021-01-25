#ifndef _WANGYONGLIN_LOG_H_INCLUDE_
#define _WANGYONGLIN_LOG_H_INCLUDE_

#include <wangyonglin/config.h>
#include <wangyonglin/core.h>
typedef struct wangyonglin_log_s wangyonglin_log_t;

typedef enum {
	LOG_INFO,LOG_DEBUG,LOG_WARN,LOG_ERROR,LOG_EMERG
}wangyonglin_log_levels_t;

struct wangyonglin_log_s{
	char  error_log[1024];
	char  access_log[1024];
};
void wangyonglin_log_conf(wangyonglin_log_t *log);
int  wangyonglin_log_init(wangyonglin_log_t * log);
void wangyonglin_log_info(const char *fmt, ...);

void wangyonglin_log_error(wangyonglin_log_levels_t level,const char *format, ...);


#endif /**_WANGYONGLIN_LOG_H_INCLUDE_**/
