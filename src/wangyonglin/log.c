#include <wangyonglin/config.h>
#include <wangyonglin/core.h>
wangyonglin_log_t * __log_t;
void wangyonglin_log_info(const char *format, ...){
	if(__log_t->access_log == NULL && __log_t->access_log  == ""){
		fprintf(stderr,"_log_t->access_log : not null \n");
		exit(-1);
	}

	struct tm * t;

		if(wangyonglin_file_exists(__log_t->access_log)==0){
			fprintf(stderr,"it not exists : %s \n",__log_t->access_log);
			exit(-1);
		}else{
			int ret= open(__log_t->access_log, O_RDWR|O_CREAT, 0640);
			if(ret!=-1){
				close(ret);
			}
			
		}

			FILE* fd = fopen(__log_t->access_log,"a");
			if(fd==NULL){
				fprintf(stderr,"it open fait : %s \n",__log_t->access_log);
				exit(-1);
			}
			t=wangyonglin_time_now();
			va_list  args;
			va_start(args, format);			

			fprintf(fd,"%04d-%02d-%02d %02d:%02d:%02d		",t->tm_year,t->tm_mon,t->tm_mday,t->tm_hour,t->tm_min,t->tm_sec);		
			vfprintf (fd, format, args);
			fputc( '\r', fd );
			fputc( '\n', fd ); 
			fflush(fd);
			va_end(args);
			fclose(fd);
		
}
int  wangyonglin_log_init(wangyonglin_log_t * log){
	if(__log_t == NULL){
		__log_t = (wangyonglin_log_t *)malloc(sizeof(wangyonglin_log_t));
		memset(__log_t,0,sizeof(wangyonglin_log_t));	
	}
	if(log!=NULL){
		__log_t = log;
		return 0;
	}

	return -1;
}
void wangyonglin_log_error(wangyonglin_log_levels_t level,const char *format, ...){
	if(__log_t->error_log == NULL){
		fprintf(stderr,"_log_t->error_log : not null \n");
		exit(-1);
	}

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

		if(wangyonglin_file_exists(__log_t->error_log)==0){
			fprintf(stderr,"it not exists : %s \n",__log_t->error_log);
			exit(-1);
		}else{
			int ret= open(__log_t->error_log, O_RDWR|O_CREAT, 0640);
			if(ret!=-1){
				close(ret);
			}
			
		}

			FILE* fd = fopen(__log_t->error_log,"a+");
			if(fd==NULL){
				fprintf(stderr,"it open fait : %s \n",__log_t->error_log);
				exit(-1);
			}
			t=wangyonglin_time_now();
			va_list  args;
			va_start(args, format);			

			fprintf(fd,"%04d-%02d-%02d %02d:%02d:%02d	%s :	",t->tm_year,t->tm_mon,t->tm_mday,t->tm_hour,t->tm_min,t->tm_sec,err_levels);		
			vfprintf(fd,format,args);
			fputc( '\r', fd );
			fputc( '\n', fd ); 
			fflush(fd);
			va_end(args);
			fclose(fd);
		
}