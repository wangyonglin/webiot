#include <wangyonglin/linux.h>
#include <wangyonglin/wangyonglin.h>
#include <mosquitto/mosquitto.h>
#include <mosquitto.h>
#include <https/https.h>
#include <https/openssl.h>
#include <public/hexstring.h>
wangyonglin_signal_t signal_t;
uint8_t tmp[1024];
struct wangyonglin__buffer payload_data_t;
/*
void applicatio_signal_callback(int signum, siginfo_t *s_t, void *p)
{
	if (signum == SIGUSR1)
	{
		wangyonglin_mosquitto_publish_t *publish_t = (wangyonglin_mosquitto_publish_t *)s_t->si_value.sival_ptr;
		struct wangyonglin__config *config = publish_t->config;
		//struct mosquitto *mosq = publish_t->mosquitto_t->mosq;
		if (publish_t != NULL)
		{
			if (publish_t->topic.data != NULL)
			{
				memset(&tmp, 0, 1024);
				wangyonglin_string_hex(publish_t->payload.data, tmp); 
				mosquitto__publist(config,publish_t->topic.data, tmp, strlen(tmp));
			}
		}
	}
}*/
void applicatio_signal_callback(int signum, siginfo_t *s_t, void *p)
{
	int rc;
	if (signum == SIGUSR1)
	{
		https__request_t *request_t = (https__request_t *)s_t->si_value.sival_ptr;
		struct wangyonglin__config *config = request_t->config;
		if (request_t != NULL)
		{
			if (request_t->topic.data != NULL)
			{
				buffer__null(&payload_data_t);
				public__hexstring(request_t->payload.data,&payload_data_t);
				rc = mosquitto__publist(config, request_t->topic.data, payload_data_t.val, strlen(payload_data_t.val));
				switch (rc)
				{
				case MOSQ_ERR_SUCCESS:
					https__success(request_t, "on success");
					break;
				case MOSQ_ERR_INVAL:
					https__failure(request_t, MOSQ_ERR_INVAL, "if the input parameters were invalid.");
					break;
				case MOSQ_ERR_NOMEM:
					https__failure(request_t, MOSQ_ERR_NOMEM, "if an out of memory condition occurred.");
					break;
				case MOSQ_ERR_NO_CONN:
					https__failure(request_t, MOSQ_ERR_NO_CONN, "if the client isn't connected to a broker.");
					break;
				case MOSQ_ERR_PROTOCOL:
					https__failure(request_t, MOSQ_ERR_PROTOCOL, "if there is a protocol error communicating with the broker.");
					break;
				case MOSQ_ERR_PAYLOAD_SIZE:
					https__failure(request_t, MOSQ_ERR_PAYLOAD_SIZE, "if payloadlen is too large.");

					break;
				case MOSQ_ERR_MALFORMED_UTF8:
					https__failure(request_t, MOSQ_ERR_MALFORMED_UTF8, "if the topic is not valid UTF-8.");

					break;
				case MOSQ_ERR_DUPLICATE_PROPERTY:
					https__failure(request_t, MOSQ_ERR_DUPLICATE_PROPERTY, "if a property is duplicated where it is forbidden.");

					break;
				case MOSQ_ERR_QOS_NOT_SUPPORTED:
					https__failure(request_t, MOSQ_ERR_QOS_NOT_SUPPORTED, "if the QoS is greater than that supported by the broker.");

					break;
				case MOSQ_ERR_OVERSIZE_PACKET:
					https__failure(request_t, MOSQ_ERR_OVERSIZE_PACKET, "if the resulting packet would be larger than supported by the broker.");

					break;
				default:
					https__failure(request_t, 444, "other errors.");
					break;
				}
						}
		}
	}
}
int application(struct wangyonglin__config *config)
{
	buffer(&payload_data_t, 1024);
	wangyonglin_openssl_init();
	wangyonglin_signal_action(&signal_t, SIGUSR1, &applicatio_signal_callback);
	mosquitto__appcation(config, &signal_t);
	https__application(config, &signal_t);
	wangyonglin_openssl_cleanup();
	buffer__cleanup(&payload_data_t);
	return ERR_SUCCESS;
}