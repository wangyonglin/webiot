#include <wangyonglin/config.h>
#include <wangyonglin/core.h>
#include <mosquitto/mosquitto.h>
#include <https/https.h>
wangyonglin_signal_t signal_t;
uint8_t  tmp[1024];
void wangyonglin_signal_callback(int signum, siginfo_t *s_t, void *p)
{	
	if (signum == SIGUSR1)
	{
		wangyonglin_mosquitto_publish_t *publish_t = (wangyonglin_mosquitto_publish_t *)s_t->si_value.sival_ptr;
		struct mosquitto *mosq = publish_t->mosquitto_t->mosq;
		if (publish_t != NULL)
		{
			if (publish_t->topic.data != NULL)
			{
				memset(&tmp,0,1024);
				wangyonglin_string_hex(publish_t->payload.data, tmp);
				wangyonglin_mosquitto_publist(publish_t->topic.data,tmp,strlen(tmp));		
			}
		}
	}
}
int main(int argc, char *argv[])
{

	int ret = 0;
	ret = wangyonglin_system_init("/usr/local/wangyonglin/conf/wangyonglin.conf", 1);
	if (ret != 0)
	{
		fprintf(stderr, "System load config err %d", ret);
		exit(EXIT_FAILURE);
	}

	wangyonglin_signal_action(&signal_t, SIGUSR1, &wangyonglin_signal_callback);
	wangyonglin_mosquitto_appcation(&signal_t);
	https_restful_appcation(&signal_t);

	return EXIT_SUCCESS;
}
