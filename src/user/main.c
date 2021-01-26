#include <wangyonglin/config.h>
#include <wangyonglin/core.h>
#include <mosquitto/service.h>
#include <https/https.h>
wangyonglin_signal_t signal_t;
void wangyonglin_signal_callback(int signum, siginfo_t *s_t, void *p)
{
	/*
	int myint = 0;
	printf("wangyonglin_signal_callback signum : %d \n", signum);
	myint = s_t->si_value.sival_int;
	printf("%d, %d \n", myint, s_t->si_int);
	printf("%s, %s \n", (char *)s_t->si_value.sival_ptr, (char *)s_t->si_ptr);
	*/
	switch (signum)
	{
	case SIGUSR1:
			printf("%s, %s \n", (char *)s_t->si_value.sival_ptr, (char *)s_t->si_ptr);
		break;
	case SIGUSR2:

		break;

	default:
		printf("\twangyonglin_signal_callback\n");
		break;
	}
}
int main(int argc, char *argv[])
{

	wangyonglin(argc, argv);
	wangyonglin_signal_action(&signal_t, SIGUSR1, &wangyonglin_signal_callback);
	//https_restful_t restful;
	//restful.signal_t = &signal_t;
	//https_restful_conf(&restful);
	//https_restful_start(&restful);
	wangyonglin_mosquitto_start();
	for (;;)
	{
		sleep(5);
		wangyonglin_signal_queue(&signal_t,SIGUSR1, 100, "wangxiaoli");
	}
	return EXIT_SUCCESS;
}
