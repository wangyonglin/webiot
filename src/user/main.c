#include <wangyonglin/config.h>
#include <wangyonglin/core.h>
#include <mosquitto/service.h>
#include <https/https.h>

int main(int argc, char *argv[])
{
	
	wangyonglin_signal_t signal_t;
	wangyonglin(argc, argv);
	wangyonglin_signal_action(&signal_t,SIGUSR1);
	https_restful_t restful;
	restful.signal_t=&signal_t;
	https_restful_conf(&restful);
	https_restful_start(&restful);
	//wangyonglin_mosquitto_start();
	
	return EXIT_SUCCESS;
}
