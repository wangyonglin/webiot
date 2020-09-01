#include <wangyonglin/config.h>
#include <wangyonglin/core.h>

int main(){

	printf("hello wangyonglin \n");
	pid_t pid = wangyonglin_pid_create("/usr/local/wangyonglin/wangyonglin.pid");
	if(wangyonglin_daemon()==WANGYONGLIN_OK){
		
	}
	for(;;){
		sleep (10);
		wangyonglin_log_error(LOG_INFO,"wang run OK PID:%d",pid);
	}

	return 0;
}
