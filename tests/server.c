#include<sys/socket.h>
#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
#include<evhttp.h>
#include<string.h>
#include<err.h>
#define NTHREADS 5
 
typedef struct httpd_info{
	struct event_base *base;
	struct evhttp *httpd;
}httpd_info;
void print_request(struct evhttp_request *request){
	switch(request->type)
	{
		case EVHTTP_REQ_GET:
		    printf("GET");
		    break;
		case EVHTTP_REQ_POST:
		    printf("POST");
		    break;
		case EVHTTP_REQ_HEAD:
		    printf("HEAD");
		    break;
		case EVHTTP_REQ_PUT:
		    printf("PUT");
		    break;
		case EVHTTP_REQ_DELETE:
		    printf("DELETE");
		    break;
		case EVHTTP_REQ_OPTIONS:
		    printf("OPTIONS");
		    break;
		case EVHTTP_REQ_TRACE:
		    printf("TRACE");
		    break;
		case EVHTTP_REQ_CONNECT:
		    printf("CONNECT");
		    break;
		case EVHTTP_REQ_PATCH:
		    printf("PATCH");
		    break;
		default:
			printf("UNKNOWN");
	}
	printf(" %s \n",request->uri);
    struct evkeyvalq *headers = evhttp_request_get_input_headers(request);
    struct evkeyval* kv = headers->tqh_first;
    while (kv) {
        printf("%s: %s\n", kv->key, kv->value);
        kv = kv->next.tqe_next;
    }
	struct evbuffer *buffer=NULL;
	buffer=evhttp_request_get_input_buffer(request);
	int len=evbuffer_get_length(buffer);
	char *data=malloc(len+1);
	data[len]='\0';
	evbuffer_copyout(buffer,data,len);
	printf("\n%s\n",data);
	evhttp_clear_headers(headers);
	free(data);
 
}
void testing(struct evhttp_request * request,void * args){
	if (request==NULL)
	{
		printf("request timeout\n");
		return;
	}
	
	printf("===THREAD %ld===\n",pthread_self());
	printf("IP: %s:%d\n",request->remote_host,request->remote_port);
    print_request(request);
    //const char *uri=evhttp_request_get_uri(request);
	struct evbuffer *buffer=evbuffer_new();
	//evbuffer_add(buffer,"coucou !",8);
	evbuffer_add_printf(buffer,"Hello World!");
	evhttp_add_header(evhttp_request_get_output_headers(request),"Content-Type","text/plain");
	evhttp_send_reply(request,HTTP_OK,"OK",buffer);
	evbuffer_free(buffer);
	
	return;
	
}
void notfound(struct evhttp_request * request,void * args){
	evhttp_send_error(request,HTTP_NOTFOUND,"Not Found");
}
void *dispatch(void *args){
	struct httpd_info *info=(struct httpd_info *)args;
	printf("thread %ld start\n",pthread_self());
	event_base_dispatch(info->base);
	printf("thread %ld done\n",pthread_self());
	event_base_free(info->base);
	evhttp_free(info->httpd);
}
int bind_socket(){
	int ret,server_socket,opt=1;
	server_socket=socket(AF_INET,SOCK_STREAM|SOCK_NONBLOCK,0);//NOTE 多线程evhttp必须非阻塞
	if (server_socket<0)
        errx(-1,"ERROR get socket: %d\n",server_socket);
 
	setsockopt(server_socket,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
	struct sockaddr_in addr;
	memset(&addr,0,sizeof(addr));
	addr.sin_family=AF_INET;
	addr.sin_addr.s_addr=INADDR_ANY;
	addr.sin_port=htons(8080);
	ret=bind(server_socket,(struct sockaddr*)&addr,sizeof(struct sockaddr));
	if(ret<0)
        errx(-1,"bind error\n");
 
	listen(server_socket,1024);
	return server_socket;
}
int main(){
    pthread_t ths[NTHREADS];
	httpd_info info_arr[NTHREADS],*pinfo;
	int i,ret,opt=1,server_socket;
	server_socket=bind_socket();
	
	for(i=0;i<NTHREADS;i++)
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
 
		evhttp_set_cb(pinfo->httpd,"/testing",testing,0);
		evhttp_set_gencb(pinfo->httpd,notfound,0);
		ret=pthread_create(&ths[i],NULL,dispatch,pinfo);
	}
	for(i=0;i<NTHREADS;i++)
	{
		pthread_join(ths[i],NULL);
	}
    
 
}