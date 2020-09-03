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
#define HTTPD_SIGNATURE   "www.wangyonglin.com"
#define BUF_MAX 1024*16
 int httpd_option_timeout = 120; //in seconds
  char * ptr = "{\"firstName\":\"Brett\"}";
//解析post请求数据
void get_post_message(char *buf, struct evhttp_request *req)
{
	size_t post_size = 0;
	
	post_size = evbuffer_get_length(req->input_buffer);//获取数据长度
	printf("====line:%d,post len:%d\n",__LINE__,post_size);
	if (post_size <= 0)
	{
		printf("====line:%d,post msg is empty!\n",__LINE__);
		return;
	}
	else
	{
		size_t copy_len = post_size > BUF_MAX ? BUF_MAX : post_size;
		printf("====line:%d,post len:%d, copy_len:%d\n",__LINE__,post_size,copy_len);
		memcpy(buf, evbuffer_pullup(req->input_buffer,-1), copy_len);
		buf[post_size] = '\0';
		printf("====line:%d,post msg:%s\n",__LINE__,buf);
	}
}

//解析http头，主要用于get请求时解析uri和请求参数
char *find_http_header(struct evhttp_request *req,struct evkeyvalq *params,const char *query_char)
{
	if(req == NULL || params == NULL || query_char == NULL)
	{
		printf("====line:%d,%s\n",__LINE__,"input params is null.");
		return NULL;
	}
	
	struct evhttp_uri *decoded = NULL;
	char *query = NULL;	
	char *query_result = NULL;
	const char *path;
	const char *uri = evhttp_request_get_uri(req);//获取请求uri
	
	if(uri == NULL)
	{
		printf("====line:%d,evhttp_request_get_uri return null\n",__LINE__);
		return NULL;
	}
	else
	{
		printf("====line:%d,Got a GET request for <%s>\n",__LINE__,uri);
	}
	
	//解码uri
	decoded = evhttp_uri_parse(uri);
	if (!decoded) 
	{
		printf("====line:%d,It's not a good URI. Sending BADREQUEST\n",__LINE__);
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
		printf("====line:%d,path is:%s\n",__LINE__,path);
	}
	
	//获取uri中的参数部分
	query = (char*)evhttp_uri_get_query(decoded);
	if(query == NULL)
	{
		printf("====line:%d,evhttp_uri_get_query return null\n",__LINE__);
		return NULL;
	}
	
	//查询指定参数的值
	evhttp_parse_query_str(query, params);			
	query_result = (char*)evhttp_find_header(params, query_char);
	
	return query_result;
}

//处理get请求
void http_handler_testget_msg(struct evhttp_request *req,void *arg)
{
	if(req == NULL)
	{
		printf("====line:%d,%s\n",__LINE__,"input param req is null.");
		return;
	}
	printf("### THREAD  IP: %s:%d\n",req->remote_host,req->remote_port);
	char *sign = NULL;
	char *data = NULL;
	struct evkeyvalq sign_params = {0};
	sign = find_http_header(req,&sign_params,"sign");//获取get请求uri中的sign参数
	if(sign == NULL)
	{
		printf("====line:%d,%s\n",__LINE__,"request uri no param sign.");
	}
	else
	{
		printf("====line:%d,get request param: sign=[%s]\n",__LINE__,sign);
	}
	
	data = find_http_header(req,&sign_params,"data");//获取get请求uri中的data参数
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
    evhttp_add_header(req->output_headers, "Server", HTTPD_SIGNATURE);
    evhttp_add_header(req->output_headers, "Content-Type", "application/json;charset=UTF-8");
    evhttp_add_header(req->output_headers, "Connection", "keep-alive");


	//回响应
	struct evbuffer *retbuff = NULL;
	retbuff = evbuffer_new();
	if(retbuff == NULL)
	{
		printf("====line:%d,%s\n",__LINE__,"retbuff is null.");
		return;
	}

	evbuffer_add_printf(retbuff,ptr);
	evhttp_send_reply(req,HTTP_OK,"OK",retbuff);
	evbuffer_free(retbuff);
}

//处理post请求
void http_handler_testpost_msg(struct evhttp_request *req,void *arg)
{
	if(req == NULL)
	{
		printf("====line:%d,%s\n",__LINE__,"input param req is null.");
		return;
	}
	
	char buf[BUF_MAX] = {0};
	get_post_message(buf, req);//获取请求数据，一般是json格式的数据
	if(buf == NULL)
	{
		printf("====line:%d,%s\n",__LINE__,"get_post_message return null.");
		return;
	}
	else
	{
		//可以使用json库解析需要的数据
		printf("====line:%d,request data:%s",__LINE__,buf);
	}
	
	//回响应
	struct evbuffer *retbuff = NULL;
	retbuff = evbuffer_new();
	if(retbuff == NULL)
	{
		printf("====line:%d,%s\n",__LINE__,"retbuff is null.");
		return;
	}
	evbuffer_add_printf(retbuff,"Receive post request,Thamks for the request!");
	evhttp_send_reply(req,HTTP_OK,"Client",retbuff);
	evbuffer_free(retbuff);
}

int main()
{
	struct evhttp *http_server = NULL;
	short http_port = 9000;
	char *http_addr = "127.0.0.1";
	
	//初始化
	event_init();
	//启动http服务端
	http_server = evhttp_start(http_addr,http_port);
	if(http_server == NULL)
	{
		printf("====line:%d,%s\n",__LINE__,"http server start failed.");
		return -1;
	}
	
	//设置请求超时时间(s)
	evhttp_set_timeout(http_server,httpd_option_timeout);
	//设置事件处理函数，evhttp_set_cb针对每一个事件(请求)注册一个处理函数，
	//区别于evhttp_set_gencb函数，是对所有请求设置一个统一的处理函数
	evhttp_set_cb(http_server,"/me/testpost",http_handler_testpost_msg,NULL);
	evhttp_set_cb(http_server,"/me/testget",http_handler_testget_msg,NULL);
	
	//循环监听
	event_dispatch();
	//实际上不会释放，代码不会运行到这一步
	evhttp_free(http_server);
		
	return 0;
}