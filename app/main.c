#include <wangyonglin/config.h>
#include <wangyonglin/core.h>
#include <cjson/json.h>



#include <httpserver.h>
#include <jsonresult.h>

#define HTTPD_SIGNATURE   "www.wangyonglin.com"
#define BUF_MAX 1024*16
 int httpd_option_timeout = 120; //in seconds

void testing(struct evhttp_request * request,void * args){
	if (request==NULL)
	{
		printf("====line:%d,%s\n",__LINE__,"input param req is null.");
		return;
	}
	printf("===THREAD %ld===\n",pthread_self());
	printf("IP: %s:%d\n",request->remote_host,request->remote_port);
	
	char *sign = NULL;
	char *data = NULL;
	struct evkeyvalq sign_params = {0};
	sign = wangyonglin_httpserver_header(request,&sign_params,"sign");//获取get请求uri中的sign参数
	if(sign == NULL)
	{
		printf("====line:%d,%s\n",__LINE__,"request uri no param sign.");
	}
	else
	{
		printf("====line:%d,get request param: sign=[%s]\n",__LINE__,sign);
	}
	
	data = wangyonglin_httpserver_header(request,&sign_params,"data");//获取get请求uri中的data参数
	if(data == NULL)
	{
		printf("====line:%d,%s\n",__LINE__,"request uri no param data.");
	}
	else
	{
		printf("====line:%d,get request param: data=[%s]\n",__LINE__,data);
	}
	printf("\n");
	
	wangyonglin_jsonresult_success(request,"OK","wangyonglin");
	return;
	
}

int main(){
	int __fd;
	wangyonglin_pid_create("/usr/local/wangyonglin/wangyonglin.pid");
	wangyonglin_daemon();
	__fd= wangyonglin_httpserver_create(80,1024);
	wangyonglin_httpserver_build(__fd,10,httpd_option_timeout,"/testing",testing);
	return 0;
}
