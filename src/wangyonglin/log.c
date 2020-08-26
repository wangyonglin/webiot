#include <wangyonglin/config.h>
#include <wangyonglin/core.h>

void wangyonglin_log_error(wangyonglin_log_levels_t level,const char *fmt, ...){

	struct tm * t;
	wangyonglin_buffer_t err_levels[16];
		switch (level)
			{
				case LOG_ERROR:
				strcpy(err_levels,"ERROR");
				
				break;
				case LOG_DEBUG:
				strcpy(err_levels,"DEBUG");
				break;
				case LOG_EMERG:
				strcpy(err_levels,"EMERG");
				break;
				case LOG_WARN:
				strcpy(err_levels,"WARN");	
				break;
			default:
				strcpy(err_levels,"INFO");	
				break;
			}
		char name[]="/usr/local/wangyonglin/log/error.log";
		if(wangyonglin_file_exists(name)==0){
			fprintf(stderr,"it not exists : %s \n",name);
			exit(-1);
		}
			FILE* fd = fopen(name,"a+");
			if(fd==NULL){
				fprintf(stderr,"it open fait : %s \n",name);
				exit(-1);
			}
			t=wangyonglin_time_now();
			va_list  args;
			va_start(args, fmt);			

			fprintf(fd,"%d-%d-%d %d:%d:%d	%s :	",t->tm_year,t->tm_mon,t->tm_mday,t->tm_hour,t->tm_min,t->tm_sec,err_levels);		
			fprintf(fd,fmt,args);
			fputc( '\r', fd );
			fputc( '\n', fd ); 
			fflush(fd);
			va_end(args);
			fclose(fd);
		
		
		
}