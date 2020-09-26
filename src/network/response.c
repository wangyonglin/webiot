#include <wangyonglin/config.h>
#include <wangyonglin/core.h>
#include <cjson/json.h>
#include <network/response.h>
//success   response
//failure
#define HTTPD_SIGNATURE   "www.wangyonglin.com"
void network_response_headers(struct evhttp_request * request){
	  /* 输出到客户端 */
   // evhttp_add_header(request->output_headers, "Author", "admin@wangyonglin.com");
    evhttp_add_header(request->output_headers, "Service", HTTPD_SIGNATURE);
    evhttp_add_header(request->output_headers, "Content-Type", "application/json;charset=UTF-8");
    evhttp_add_header(request->output_headers, "Connection", "keep-alive");
}
int  network_response_success(struct evhttp_request * request,const char *reason,char * result){
   	network_response_headers(request);
    //回响应
	struct evbuffer *buffer = NULL;
	buffer = evbuffer_new();
	if(buffer == NULL)
	{
		printf("====line:%d,%s\n",__LINE__,"retbuff is null.");
		return -1;
	}
	
    /* 输出 JSON*/
    cJSON* root = cJSON_CreateObject(); //创建一个对象
    if (!root) return -1;

    cJSON_AddTrueToObject(root,"success");
    cJSON_AddStringToObject(root, "reason", reason);
    cJSON_AddStringToObject(root, "result", result);
    cJSON_AddNumberToObject(root, "errcode", HTTP_OK);
    struct tm * t=NULL;
    t=wangyonglin_core_localtime();

    char __buftime[50]={0};
    sprintf(__buftime,"%04d-%02d-%02d %02d:%02d:%02d",t->tm_year,t->tm_mon,t->tm_mday,t->tm_hour,t->tm_min,t->tm_sec);
    cJSON_AddStringToObject(root, "timestamp", __buftime);
    char* __json = cJSON_Print(root);

    if (__json != NULL)
    {
		
		evbuffer_add_printf(buffer,__json);
		evhttp_send_reply(request,HTTP_OK,"OK",buffer);
        free(__json);
    }

    cJSON_Delete(root);

	evbuffer_free(buffer);

    return 0;
}


int  network_response_failure(struct evhttp_request *request, int error, const char *reason){
     	network_response_headers(request);  
	  //回响应
	struct evbuffer *buffer = NULL;
	buffer = evbuffer_new();
	if(buffer == NULL)
	{
		printf("====line:%d,%s\n",__LINE__,"retbuff is null.");
		return -1;
	}
    /* 输出 JSON*/
    cJSON* root = cJSON_CreateObject(); //创建一个对象
    if (!root) return -1;

    cJSON_AddFalseToObject(root,"success");
    cJSON_AddStringToObject(root, "reason", reason);
    cJSON_AddStringToObject(root, "result", "");
    cJSON_AddNumberToObject(root, "errcode", error);
    struct tm * t=NULL;
    t=wangyonglin_core_localtime();

    char __buftime[50]={0};
    sprintf(__buftime,"%04d-%02d-%02d %02d:%02d:%02d",t->tm_year,t->tm_mon,t->tm_mday,t->tm_hour,t->tm_min,t->tm_sec);
    cJSON_AddStringToObject(root, "timestamp", __buftime);
    char* __json = cJSON_Print(root);

    if (__json != NULL)
    {	
		//evhttp_send_error(request,error,__json);
        evbuffer_add_printf(buffer,__json);
		evhttp_send_reply(request,error,reason,buffer);
        free(__json);
    }

    cJSON_Delete(root);

	evbuffer_free(buffer);

    return 0;
}



