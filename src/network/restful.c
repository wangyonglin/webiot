#include <wangyonglin/config.h>
#include <wangyonglin/core.h>

#include <network/restful.h>
#include <network/response.h>

void *network_restful_dispatch(void *args);

int network_restful_bind(network_restful_t *restful)
{

    if ((restful->sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) /*建立一个流式套接字*/
    {
        printf("create socket error: %s(errno: %d)\n", strerror(errno), errno);
        return wangyonglin_result_error;
    }

    /*设置服务端地址*/
    struct sockaddr_in sockaddr;
    bzero(&sockaddr, sizeof(struct sockaddr_in));
    sockaddr.sin_family = AF_INET;                /*AF_INET表示 IPv4 Intern 协议*/
    sockaddr.sin_addr.s_addr = htonl(INADDR_ANY); /*INADDR_ANY 可以监听任意IP */
    sockaddr.sin_port = htons(restful->port);     /*设置端口*/
    socklen_t socklen = sizeof(struct sockaddr_in);
    int opt = 1;
    // sockfd为需要端口复用的套接字
    setsockopt(restful->sockfd, SOL_SOCKET, SO_REUSEADDR, (const void *)&opt, sizeof(opt));
    /*绑定地址结构到套接字描述符*/
    if (bind(restful->sockfd, (struct sockaddr *)&sockaddr, socklen) == -1)
    {
        printf("bind socket error: %s(errno: %d)\n", strerror(errno), errno);

        return wangyonglin_result_error;
    }

    /*设置监听队列，这里设置为1，表示只能同时处理一个客户端的连接*/
    if (listen(restful->sockfd, restful->backlog) == -1)
    {
        printf("listen socket error: %s(errno: %d)\n", strerror(errno), errno);

        return wangyonglin_result_error;
    }
	int flags;
	if ((flags = fcntl(restful->sockfd, F_GETFL, 0)) < 0 || fcntl(restful->sockfd, F_SETFL, flags | O_NONBLOCK) < 0)
		return wangyonglin_result_failure;
    return wangyonglin_result_success;
}

int network_restful_run(network_restful_t *restful)
{

	
    int nthreads = 10;
    pthread_t ths[nthreads];
    httpd_info info_arr[nthreads], *pinfo;
    int i, ret, opt = 1;
    for (i = 0; i < nthreads; i++)
    {
        pinfo = &info_arr[i];
        pinfo->base = event_base_new();
        if (pinfo->base == NULL)
            errx(-1, "ERROR new base\n");
        pinfo->httpd = evhttp_new(pinfo->base);
        if (pinfo->httpd == NULL)
            errx(-1, "ERROR new evhttp\n");
        ret = evhttp_accept_socket(pinfo->httpd,restful->sockfd);
        if (ret != 0)
            errx(-1, "Error evhttp_accept_socket\n");

        evhttp_set_cb(pinfo->httpd, "/testing", network_restful_get,restful);
        evhttp_set_gencb(pinfo->httpd, network_restful_notfound, 0);
        ret = pthread_create(&ths[i], NULL, network_restful_dispatch, pinfo);
    }
    for (i = 0; i < nthreads; i++)
    {
        pthread_join(ths[i], NULL);
    }
	wangyonglin_message_msgctl(restful->id);
    return ret;
}

void network_restful_conf(network_restful_t *restful)
{
    wangyonglin_conf_get(&restful->port, "restful:port", wangyonglin_type_int);
    wangyonglin_conf_get(&restful->backlog, "restful:backlog", wangyonglin_type_int);
}
void network_restful_notfound(struct evhttp_request *request, void *args)
{
	wangyonglin_log_info("### IP: %s:%d CODE: %d URL: %s ", request->remote_host, request->remote_port, HTTP_NOTFOUND, evhttp_request_get_uri(request));
	network_response_failure(request, HTTP_NOTFOUND, "Not Found");
}

//处理get请求
void network_restful_get(struct evhttp_request *req, void *arg)
{
	network_restful_t *restful = (network_restful_t*)arg;
	int rc = 0;
	wangyonglin_log_info("### IP: %s:%d CODE: %d URL: %s", req->remote_host, req->remote_port, HTTP_OK, evhttp_request_get_uri(req));
	if (req == NULL)
	{
		network_response_failure(req, HTTP_BADREQUEST, "input param request is null.");
		return;
	}

	char *sign = NULL;
	char *data = NULL;
	struct evkeyvalq sign_params = {0};
	sign = network_restful_params(req, &sign_params, "sign"); //获取get请求uri中的sign参数
	if (sign == NULL)
	{
		network_response_failure(req, HTTP_BADREQUEST, "request uri no param sign.");
		return;
	}

	data = network_restful_params(req, &sign_params, "data"); //获取get请求uri中的data参数
	if (data == NULL)
	{
		network_response_failure(req, HTTP_BADREQUEST, "request uri no param data.");
		return;
	}
	
	wangyonglin_pipe_write(restful->pipe,data,strlen(data));
	network_response_success(req, data, req->remote_host);
	return;
}

//解析http头，主要用于get请求时解析uri和请求参数
char *network_restful_params(struct evhttp_request *req, struct evkeyvalq *params, const char *query_char)
{
	if (req == NULL || params == NULL || query_char == NULL)
	{
		network_response_failure(req, HTTP_BADREQUEST, "input params is null.");
		return NULL;
	}

	struct evhttp_uri *decoded = NULL;
	char *query = NULL;
	char *query_result = NULL;
	const char *path;
	const char *uri = evhttp_request_get_uri(req); //获取请求uri

	if (uri == NULL)
	{
		printf("====line:%d,evhttp_request_get_uri return null\n", __LINE__);
		return NULL;
	}

	//解码uri
	decoded = evhttp_uri_parse(uri);
	if (!decoded)
	{
		printf("====line:%d,It's not a good URI. Sending BADREQUEST\n", __LINE__);
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
		printf("====line:%d,path is:%s\n", __LINE__, path);
	}

	//获取uri中的参数部分
	query = (char *)evhttp_uri_get_query(decoded);
	if (query == NULL)
	{
		printf("====line:%d,evhttp_uri_get_query return null\n", __LINE__);
		return NULL;
	}

	//查询指定参数的值
	evhttp_parse_query_str(query, params);
	query_result = (char *)evhttp_find_header(params, query_char);

	return query_result;
}
void *network_restful_dispatch(void *args)
{
	struct httpd_info *info = (struct httpd_info *)args;
	event_base_dispatch(info->base);
	event_base_free(info->base);
	evhttp_free(info->httpd);

}
void netwrok_restful_close(network_restful_t * restful){
	close(restful->sockfd);
}
int network_restful_message(network_restful_t * restful){
	restful->id= wangyonglin_message_create();
}