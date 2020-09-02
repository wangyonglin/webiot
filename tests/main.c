#include <wangyonglin/config.h>
#include <wangyonglin/core.h>
#include <cjson/json.h>

#include <stdio.h>
#include <stdlib.h>
#include <evhttp.h>
#include <event.h>
#include <string.h>
#include "event2/http.h"
#include "event2/event.h"
#include "event2/buffer.h"
#include "event2/bufferevent.h"
#include "event2/bufferevent_compat.h"
#include "event2/http_struct.h"
#include "event2/http_compat.h"
#include "event2/util.h"
#include "event2/listener.h"
#include "http.h"

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
	sign = wangyonglin_http_header(request,&sign_params,"sign");//获取get请求uri中的sign参数
	if(sign == NULL)
	{
		printf("====line:%d,%s\n",__LINE__,"request uri no param sign.");
	}
	else
	{
		printf("====line:%d,get request param: sign=[%s]\n",__LINE__,sign);
	}
	
	data = wangyonglin_http_header(request,&sign_params,"data");//获取get请求uri中的data参数
	if(data == NULL)
	{
		printf("====line:%d,%s\n",__LINE__,"request uri no param data.");
	}
	else
	{
		printf("====line:%d,get request param: data=[%s]\n",__LINE__,data);
	}
	printf("\n");
	
     /* 输出到客户端 */
	//HTTP header
    evhttp_add_header(request->output_headers, "Server", HTTPD_SIGNATURE);
    evhttp_add_header(request->output_headers, "Content-Type", "application/json;charset=UTF-8");
    evhttp_add_header(request->output_headers, "Connection", "keep-alive");


	//回响应
	struct evbuffer *buffer = NULL;
	buffer = evbuffer_new();
	if(buffer == NULL)
	{
		printf("====line:%d,%s\n",__LINE__,"retbuff is null.");
		return;
	}
	
 	cJSON* root = cJSON_CreateObject(); //创建一个对象
    if (!root) return;

    cJSON_AddStringToObject(root, "number", "00001"); //添加一个节点
    cJSON_AddStringToObject(root, "name", "zhang san");
    cJSON_AddStringToObject(root, "class", "140412");
    char* __json = cJSON_Print(root);

    if (__json != NULL)
    {
		
		evbuffer_add_printf(buffer,__json);
		evhttp_send_reply(request,HTTP_OK,"OK",buffer);
        free(__json);
    }

    cJSON_Delete(root);

	evbuffer_free(buffer);
	
	return;
	
}

int main(){
	int __fd;
	wangyonglin_pid_create("/usr/local/wangyonglin/wangyonglin.pid");
	wangyonglin_daemon();


	__fd= wangyonglin_http_create(80,1024);
	wangyonglin_http_build(__fd,10,httpd_option_timeout,"/testing",testing);
	return 0;
}
