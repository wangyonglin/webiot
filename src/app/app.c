#include <wangyonglin/linux.h>
#include <wangyonglin/wangyonglin.h>
#include <mosquitto/mosquitto.h>
#include <mosquitto.h>
#include <https/https.h>
#include <https/openssl.h>
#include <public/hexstring.h>
struct wangyonglin__buffer payload_data_t;
void msg_callback(int signum, siginfo_t *s_t, void *p)
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
				wangyonglin__buffer_null(&payload_data_t);
				public__hexstring(request_t->payload.data, &payload_data_t);
				rc = mosquitto__publist(config, request_t->topic.data, payload_data_t.data,payload_data_t.length);
				switch (rc)
				{
				case MOSQ_ERR_SUCCESS:
					https__success(request_t, "好的");
					break;
				case MOSQ_ERR_INVAL:
					https__failure(request_t, MOSQ_ERR_INVAL, "无效参数");
					break;
				case MOSQ_ERR_NOMEM:
					https__failure(request_t, MOSQ_ERR_NOMEM, "内存不足");
					break;
				case MOSQ_ERR_NO_CONN:
					https__failure(request_t, MOSQ_ERR_NO_CONN, "客户端没有连接到代理");
					break;
				case MOSQ_ERR_PROTOCOL:
					https__failure(request_t, MOSQ_ERR_PROTOCOL, "代理通信的协议错误");
					break;
				case MOSQ_ERR_PAYLOAD_SIZE:
					https__failure(request_t, MOSQ_ERR_PAYLOAD_SIZE, "有效载荷太大");

					break;
				case MOSQ_ERR_MALFORMED_UTF8:
					https__failure(request_t, MOSQ_ERR_MALFORMED_UTF8, "主题不是有效的UTF-8");

					break;
				case MOSQ_ERR_DUPLICATE_PROPERTY:
					https__failure(request_t, MOSQ_ERR_DUPLICATE_PROPERTY, "属性在禁止的地方被复制");

					break;
				case MOSQ_ERR_QOS_NOT_SUPPORTED:
					https__failure(request_t, MOSQ_ERR_QOS_NOT_SUPPORTED, "QoS大于代理支持的QoS");

					break;
				case MOSQ_ERR_OVERSIZE_PACKET:
					https__failure(request_t, MOSQ_ERR_OVERSIZE_PACKET, "得到的包大于代理支持的包");

					break;
				default:
					https__failure(request_t, 444, "其他错误");
					break;
				}
			}
		}
	}else if(signum == SIGUSR2){
		
	}
}
int application(struct wangyonglin__config *config)
{
	int rc;
	wangyonglin__buffer_register(&payload_data_t, 1024);
	https__openssl_init();
	struct wangyonglin__message  message;
	wangyonglin__message_new(&message,config);
	wangyonglin__message_sigaction(&message,SIGUSR1,&msg_callback);
	wangyonglin__message_sigaction(&message,SIGUSR2,&msg_callback);
	mosquitto__appcation(config,&message);
	https__application(config,&message);
	https__openssl_cleanup();
	wangyonglin__buffer_cleanup(&payload_data_t);
	return ERR_SUCCESS;
}
