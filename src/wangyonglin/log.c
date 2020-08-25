#include <wangyonglin/config.h>
#include <wangyonglin/core.h>
typedef u_int wangyonglin_uint_t ;

static wangyonglin_string_t err_levels[] = {
	    wangyonglin_null_string,
	    wangyonglin_string("emerg"),
	    wangyonglin_string("alert"),
	    wangyonglin_string("crit"),
	    wangyonglin_string("error"),
	    wangyonglin_string("warn"),
	    wangyonglin_string("notice"),
	    wangyonglin_string("info"),
	    wangyonglin_string("debug")
	};

void wangyonglin_file_fopen(wangyonglin_string_t file,wangyonglin_log_t * log){
		if( (log->fd=fopen(file->data,"rb") == NULL )){
			fprintf(stderr,"Fail to open file!\n");
			exit(0);  //退出程序（结束程序）
		}
}
void wangyonglin_file_fclose(wangyonglin_log_t * log){

	if(log->fd!=NULL){
		fclose(log->fd);
	}
}
void wangyonglin_log_error(wangyonglin_uint_t level,wangyonglin_log_t * log,const char *fmt, ...){
		wangyonglin_file_fopen(wangyonglin_string("/usr/local/nginx/log/error.log"),log);
		va_list  args;
	    if (log->log_level >= level) {
	        va_start(args, fmt);
	       if(log->fd!=NULL){
			   fprintf(log->fd,fmt,args);
		   }
	        va_end(args);
	    }
		wangyonglin_file_fclose(log);
}