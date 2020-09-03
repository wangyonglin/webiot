#include <wangyonglin/config.h>
#include <wangyonglin/core.h>
#include <cjson/json.h>



#include <httpserver.h>
#include <jsonresult.h>


int main(){
	wangyonglin_log_t log;
	wangyonglin_pid_t pid;
	
	fprintf(stdout,"hello wangyonglin !\n");
	
	wangyonglin_conf_open("/usr/local/wangyonglin/conf/wangyonglin.conf");
	
	strcpy(log.access_log,wangyonglin_conf_read("access_log"));
	strcpy(log.error_log,wangyonglin_conf_read("error_log"));
	
	strcpy(pid.filename,wangyonglin_conf_read("wangyonglin_pid"));

	fprintf(stdout,"log->error_log: %s\n",log.error_log);
	fprintf(stdout,"log->access_log: %s\n",log.access_log);
	fprintf(stdout,"pid->pid: %s\n",pid.filename);
	wangyonglin_pid_create(&pid);
	wangyonglin_log_init(&log);

	
//	int __fd;
	
	wangyonglin_daemon();
	//__fd= wangyonglin_httpserver_create(80,1024);
	//__fd= wangyonglin_httpserver_bindsocket(80,10240);
	//wangyonglin_httpserver_build(__fd,10,httpd_option_timeout,"/testing",testing);

	wangyonglin_httpserver_start(80,55,1024);
	wangyonglin_conf_close();
	return 0;
}
