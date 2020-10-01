#include <wangyonglin/config.h>
#include <wangyonglin/core.h>
#include <network/server.h>
#include <network/restful.h>
#define MAXLINE 4096 /* max line length */
void app_main_pipecall(void *arg)
{
	wangyonglin_pipe_t *pipe_t = (wangyonglin_pipe_t *)arg;
	ssize_t rc = 0;
	unsigned char data[MAXLINE];
	while (1)
	{
		/* code */
		bzero(&data, sizeof(data));
		rc = wangyonglin_pipe_read(pipe_t, data, MAXLINE);
		if (rc > 0)
		{
			printf("\tapp_main_pipecall\t%s \n", data);
		}
	}
}

int main(int argc, char *argv[])
{

	int rc = 0;

	wangyonglin(argc, argv);
	wangyonglin_pipe_t __pipe_t;
	wangyonglin_pipe_create(&__pipe_t);

	printf("fd[0] is : %d \n", __pipe_t.fd[0]);
	printf("fd[1] is : %d \n", __pipe_t.fd[1]);

	network_restful_t restful;
	network_restful_conf(&restful);
	restful.pipe = &__pipe_t;
	//network_restful_message(&restful);
	pthread_t pid;
	pthread_create(&pid, NULL, (void *)app_main_pipecall, &__pipe_t);
	network_restful_bind(&restful);
	network_restful_run(&restful);
	//	netwrok_restful_close(&restful);

	return rc;
}
