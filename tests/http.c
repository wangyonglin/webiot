#include <wangyonglin/config.h>
#include <wangyonglin/core.h>
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


#define NTHREADS 5


//解析http头，主要用于get请求时解析uri和请求参数
char * wangyonglin_http_header(struct evhttp_request *req,struct evkeyvalq *params,const char *query_char)
{
	if(req == NULL || params == NULL || query_char == NULL)
	{
		wangyonglin_log_error(LOG_INFO,"====line:%d,%s\n",__LINE__,"input params is null.");
		return NULL;
	}
	
	struct evhttp_uri *decoded = NULL;
	char *query = NULL;	
	char *query_result = NULL;
	const char *path;
	const char *uri = evhttp_request_get_uri(req);//获取请求uri
	
	if(uri == NULL)
	{
		wangyonglin_log_error(LOG_INFO,"====line:%d,evhttp_request_get_uri return null\n",__LINE__);
		return NULL;
	}
	else
	{
		wangyonglin_log_error(LOG_INFO,"====line:%d,Got a GET request for <%s>\n",__LINE__,uri);
	}
	
	//解码uri
	decoded = evhttp_uri_parse(uri);
	if (!decoded) 
	{
	wangyonglin_log_error(LOG_INFO,"====line:%d,It's not a good URI. Sending BADREQUEST\n",__LINE__);
		evhttp_send_error(req, HTTP_BADREQUEST, 0);
		return NULL;
	}
	//获取uri中的path部分
	path = evhttp_uri_get_path(decoded);
	if (path == NULL) 
	{
		path = "/";
	}
	else
	{
	wangyonglin_log_error(LOG_INFO,"====line:%d,path is:%s\n",__LINE__,path);
	}
	
	//获取uri中的参数部分
	query = (char*)evhttp_uri_get_query(decoded);
	if(query == NULL)
	{
		wangyonglin_log_error(LOG_INFO,"====line:%d,evhttp_uri_get_query return null\n",__LINE__);
		return NULL;
	}
	
	//查询指定参数的值
	evhttp_parse_query_str(query, params);			
	query_result = (char*)evhttp_find_header(params, query_char);
	
	return query_result;
}
int wangyonglin_http_create(uint16_t __hostshort,int __n){
	int ret,__fd,opt=1;
	__fd=socket(AF_INET,SOCK_STREAM|SOCK_NONBLOCK,0);//NOTE 多线程evhttp必须非阻塞
	if (__fd<0){
		wangyonglin_log_error(LOG_ERROR,"ERROR get socket: %d",__fd);
		exit(-1);
	}
	if(setsockopt(__fd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt))==-1){
		wangyonglin_log_error(LOG_ERROR,"setsockopt failt");
		exit(-1);
	}
	struct sockaddr_in addr;
	memset(&addr,0,sizeof(addr));
	addr.sin_family=AF_INET;
	addr.sin_addr.s_addr=INADDR_ANY;
	addr.sin_port=htons(__hostshort);
	ret=bind(__fd,(struct sockaddr*)&addr,sizeof(struct sockaddr));
	if(ret<0){
		wangyonglin_log_error(LOG_ERROR,"bind error: %d",__hostshort);
		exit(-1);
	}

	if(listen(__fd,__n)==-1){
		wangyonglin_log_error(LOG_ERROR,"listen failt");
		exit(-1);
	}
	return __fd;
}


void __notfound(struct evhttp_request * request,void * args){
	     /* 输出到客户端 */
	//HTTP headeradmin@wangyonglin
    evhttp_add_header(request->output_headers, "Server", "WANG YONGLIN");
	evhttp_add_header(request->output_headers, "Author", "admin@wangyonglin.com");
    evhttp_add_header(request->output_headers, "Content-Type", "application/json;charset=UTF-8");
    evhttp_add_header(request->output_headers, "Connection", "keep-alive");

	evhttp_send_error(request,HTTP_NOTFOUND,"Not Found");
}
void *__dispatch(void *args){
	struct httpd_info *info=(struct httpd_info *)args;
	wangyonglin_log_error(LOG_INFO,"thread %ld start\n",pthread_self());
	event_base_dispatch(info->base);
	wangyonglin_log_error(LOG_INFO,"thread %ld done\n",pthread_self());
	event_base_free(info->base);
	evhttp_free(info->httpd);
}
int wangyonglin_http_build(int __fd,uint16_t __nthreads,int __timeout,const char *path,void * cb_arg){
	pthread_t ths[__nthreads];
	httpd_info info_arr[__nthreads],*pinfo;
	int i,ret,opt=1;
	
	for(i=0;i<__nthreads;i++)
	{
		pinfo=&info_arr[i];
		pinfo->base=event_base_new();
		if (pinfo->base==NULL){
			wangyonglin_log_error(LOG_ERROR,"event_base_new failt");
			exit(-1);
		}
		
		pinfo->httpd=evhttp_new(pinfo->base);
		if (pinfo->httpd==NULL){
			wangyonglin_log_error(LOG_ERROR,"evhttp_new failt");
			exit(-1);
		}
         
		ret=evhttp_accept_socket(pinfo->httpd,__fd);
		if (ret!=0){
			wangyonglin_log_error(LOG_ERROR,"evhttp_accept_socket failt");
			exit(-1);
		}
        //evhttp_set_timeout(pinfo->httpd,__timeout);    
		evhttp_set_cb(pinfo->httpd,path,cb_arg,0);
		evhttp_set_gencb(pinfo->httpd,__notfound,0);
		ret=pthread_create(&ths[i],NULL,__dispatch,pinfo);
	}
	for(i=0;i<__nthreads;i++)
	{
		pthread_join(ths[i],NULL);
	}
	return 0;
}