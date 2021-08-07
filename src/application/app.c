#include <wangyonglin/linux.h>
#include <wangyonglin/wangyonglin.h>
#include <mosquitto/mosquitto.h>
#include <mosquitto.h>
#include <https/https.h>
#include <https/openssl.h>
#include <cjson/json.h>

void msg_callback(int signum, siginfo_t *s_t, void *p)
{
	
}
int application(configify_t *config)
{
	int rc;
	https__openssl_init();
	msgify_t message;
	msgify_init(config,&message);
	msgify_sigaction(&message, SIGUSR1, &msg_callback);
	mosquitto__appcation(config, &message);
	https__application(config, &message);
	https__openssl_cleanup();
	return ERR_SUCCESS;
}
