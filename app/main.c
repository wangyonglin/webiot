#include <wangyonglin/config.h>
#include <wangyonglin/core.h>
#include <server/tcp.h>
#include <https/restful.h>
#include <aliyun/https.h>
int main(int argc, char *argv[])
{

	int rc = 0;

	wangyonglin(argc, argv);
	wangyonglin_pipe_t pipe_t;
	if (wangyonglin_pipe_create(&pipe_t) == -1)
	{
		wangyonglin_error_exit(EXIT_FAILURE, "\twangyonglin_pipe_create failt \n");
	}

	//wangyonglin_socket_t socket_t;
	//socket_t.client_t.pipe_t=pipe_t;
	//	server_tcp_conf(&socket_t);
	//	server_tcp_start(&socket_t);
	aliyun_https_get("https://www.baidu.com");
	https_restful_t restful;
	restful.pipe = pipe_t;
	https_restful_conf(&restful);
	https_restful_start(&restful);
	return rc;
}
