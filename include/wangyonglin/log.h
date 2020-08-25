#ifndef _WANGYONGLIN_LOG_H_INCLUDE_
#define _WANGYONGLIN_LOG_H_INCLUDE_

#include <wangyonglin/config.h>
#include <wangyonglin/core.h>



struct wangyonglin_log_s{
	wangyonglin_uint_t log_level;
	FILE * fd;
	char * msg;
};


void wangyonglin_file_fopen(wangyonglin_string_t file,wangyonglin_log_t * log);
void wangyonglin_log_error(wangyonglin_uint_t level,wangyonglin_log_t * log,const char *fmt, ...);


#endif /**_WANGYONGLIN_LOG_H_INCLUDE_**/
