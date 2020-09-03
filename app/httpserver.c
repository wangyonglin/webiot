#include <wangyonglin/config.h>
#include <wangyonglin/core.h>
#include <httpserver.h>
#include <jsonresult.h>


void __httpserver_notfound(struct evhttp_request * request,void * args);
void *__httpserver_dispatch(void *args);
int __httpserver_bindsocket(int port, int backlog);
char *__httpserver_httpparams(struct evhttp_request *req,struct evkeyvalq *params,const char *query_char);
void testing(struct evhttp_request * request,void * args){
	if (request==NULL)
	{
		wangyonglin_log_error(LOG_INFO,"request timeout");
		return;
	}
	wangyonglin_log_info("### IP: %s:%d CODE: %d URL: %s",request->remote_host,request->remote_port,HTTP_OK,evhttp_request_get_uri(request));	
	wangyonglin_jsonresult_success(request,"OK",request->remote_host);
	return;
	
}
//处理get请求
void http_handler_testget_msg(struct evhttp_request *req,void *arg)
{
	wangyonglin_log_info("### IP: %s:%d CODE: %d URL: %s",req->remote_host,req->remote_port,HTTP_OK,evhttp_request_get_uri(req));
	if(req == NULL)
	{
		wangyonglin_jsonresult_failure(req,HTTP_BADREQUEST,"input param request is null.");
		return;
	}

	
	char *sign = NULL;
	char *data = NULL;
	struct evkeyvalq sign_params = {0};
	sign = __httpserver_httpparams(req,&sign_params,"sign");//获取get请求uri中的sign参数
	if(sign == NULL)
	{
		wangyonglin_jsonresult_failure(req,HTTP_BADREQUEST,"request uri no param sign.");
		return;
	}
	
	
	data = __httpserver_httpparams(req,&sign_params,"data");//获取get请求uri中的data参数
	if(data == NULL)
	{
		wangyonglin_jsonresult_failure(req,HTTP_BADREQUEST,"request uri no param data.");
		return;
	}
	

  	
	wangyonglin_jsonresult_success(req,"OK",req->remote_host);
	return;
}


int __httpserver_bindsocket(int port, int backlog) {
  int r;
  int nfd;
  nfd = socket(AF_INET, SOCK_STREAM, 0);
  if (nfd < 0) return -1;
 
  int one = 1;
  r = setsockopt(nfd, SOL_SOCKET, SO_REUSEADDR, (char *)&one, sizeof(int));
 
  struct sockaddr_in addr;
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = INADDR_ANY;
  addr.sin_port = htons(port);
 
  r = bind(nfd, (struct sockaddr*)&addr, sizeof(addr));
  if (r < 0) return -1;
  r = listen(nfd, backlog);
  if (r < 0) return -1;
 
  int flags;
  if ((flags = fcntl(nfd, F_GETFL, 0)) < 0
      || fcntl(nfd, F_SETFL, flags | O_NONBLOCK) < 0)
    return -1;
 
  return nfd;
}

void __httpserver_notfound(struct evhttp_request * request,void * args){
	wangyonglin_log_info("### IP: %s:%d CODE: %d URL: %s ",request->remote_host,request->remote_port,HTTP_NOTFOUND,evhttp_request_get_uri(request));
	wangyonglin_jsonresult_failure(request,HTTP_NOTFOUND,"Not Found");
}
void *__httpserver_dispatch(void *args){
	struct httpd_info *info=(struct httpd_info *)args;
	event_base_dispatch(info->base);
	event_base_free(info->base);
	evhttp_free(info->httpd);
}

int wangyonglin_httpserver_start(int port, int nthreads, int backlog) {

 pthread_t ths[nthreads];
	httpd_info info_arr[nthreads],*pinfo;
	int i,ret,opt=1,server_socket;
	server_socket=__httpserver_bindsocket(port,backlog);
	
	for(i=0;i<nthreads;i++)
	{
		pinfo=&info_arr[i];
		pinfo->base=event_base_new();
		if (pinfo->base==NULL)
			errx(-1,"ERROR new base\n");
		pinfo->httpd=evhttp_new(pinfo->base);
		if (pinfo->httpd==NULL)
            errx(-1,"ERROR new evhttp\n");
		ret=evhttp_accept_socket(pinfo->httpd,server_socket);
		if (ret!=0)
            errx(-1,"Error evhttp_accept_socket\n");
 
		evhttp_set_cb(pinfo->httpd,"/testing",http_handler_testget_msg,0);
		evhttp_set_gencb(pinfo->httpd,__httpserver_notfound,0);
		ret=pthread_create(&ths[i],NULL,__httpserver_dispatch,pinfo);
	}
	for(i=0;i<nthreads;i++)
	{
		pthread_join(ths[i],NULL);
	}
}

//解析http头，主要用于get请求时解析uri和请求参数
char *__httpserver_httpparams(struct evhttp_request *req,struct evkeyvalq *params,const char *query_char)
{
	if(req == NULL || params == NULL || query_char == NULL)
	{
		wangyonglin_jsonresult_failure(req,HTTP_BADREQUEST,"input params is null.");
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
