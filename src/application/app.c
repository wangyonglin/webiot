#include <wangyonglin/linux.h>
#include <wangyonglin/wangyonglin.h>
#include <mosquitto/mosquitto.h>
#include <mosquitto.h>
#include <https/https.h>
#include <https/openssl.h>
#include <cjson/json.h>
struct wangyonglin__buffer payload_data_t;
void msg_callback(int signum, siginfo_t *s_t, void *p)
{
	
}
int application(struct wangyonglin__config *config)
{

	int rc;
	wangyonglin__buffer_register(&payload_data_t, 1024);
	https__openssl_init();
	struct wangyonglin__message message;
	wangyonglin__message_new(&message, config);
	wangyonglin__message_sigaction(&message, SIGUSR1, &msg_callback);
	mosquitto__appcation(config, &message);
	https__application(config, &message);
	https__openssl_cleanup();
	wangyonglin__buffer_cleanup(&payload_data_t);
	return ERR_SUCCESS;
}
