#include <wangyonglin/config.h>
#include <wangyonglin/core.h>
#include <mosquitto/service.h>
#include <https/https.h>
#include "main.h"
wangyonglin_signal_t signal_t;
wangyonglin_mosquitto_t mosquitto_t;
wangyonglin_mqtt_t *mqtt_t;

void wangyonglin_signal_callback(int signum, siginfo_t *s_t, void *p)
{

	if (signum == SIGUSR1)
	{

		wangyonglin_mosquitto_publish_t *publish_t = (wangyonglin_mosquitto_publish_t *)s_t->si_value.sival_ptr;
		if (publish_t != NULL)
		{
			if (publish_t->topic != NULL && publish_t->topic > 0)
			{
				uint8_t data[1024] = {0};
				wangyonglin_string_hex(publish_t->payload, data);
				mosquitto_publish(mosquitto_t.mosq, NULL, publish_t->topic, strlen(data), data, 0, 0);
			}
		}
	}
}
int main(int argc, char *argv[])
{

	wangyonglin(argc, argv);
	wangyonglin_signal_action(&signal_t, SIGUSR1, &wangyonglin_signal_callback);
	wangyonglin_mosquitto_init(&mosquitto_t, &signal_t);
	wangyonglin_mosquitto_create(&mosquitto_t);
	https_restful_t restful;
	restful.signal_t = &signal_t;
	https_restful_conf(&restful);
	https_restful_start(&restful);

	return EXIT_SUCCESS;
}
