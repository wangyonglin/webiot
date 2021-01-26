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
	/*
	int myint = 0;
	printf("wangyonglin_signal_callback signum : %d \n", signum);
	myint = s_t->si_value.sival_int;
	printf("%d, %d \n", myint, s_t->si_int);
	printf("%s, %s \n", (char *)s_t->si_value.sival_ptr, (char *)s_t->si_ptr);
	*/

	if (signum == SIGUSR1)
	{
		mqtt_t = (wangyonglin_mqtt_t*)malloc(sizeof(wangyonglin_mqtt_t*));
		if (matt_json_parse(mqtt_t, (char *)s_t->si_ptr) == 0)
		{
			mosquitto_publish(mosquitto_t.mosq, NULL, mqtt_t->topic->valuestring, strlen(mqtt_t->payload->valuestring),mqtt_t->payload->valuestring, 0, 0);
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
int matt_json_parse(wangyonglin_mqtt_t *mqtt_t, char *str)
{

	//printf("str1:%s\n\n", str);
	mqtt_t->root = cJSON_Parse(str); //创建JSON解析对象，返回JSON格式是否正确
	if (!mqtt_t->root)
	{
	//	printf("JSON格式错误:%s\n\n", cJSON_GetErrorPtr()); //输出json格式错误信息
		return -1;
	}
	else
	{
		//printf("JSON格式正确:\n%s\n\n", cJSON_Print(root));
		mqtt_t->topic = cJSON_GetObjectItem(mqtt_t->root, "topic"); //获取name键对应的值的信息
		if (mqtt_t->topic->type != cJSON_String)
		{
			//printf("topic:%s\r\n", topic->valuestring);
			return -1;
		
		}
		mqtt_t->payload = cJSON_GetObjectItem(mqtt_t->root, "payload"); //获取age键对应的值的信息
		if (mqtt_t->payload->type != cJSON_String)
		{
			//printf("payload:%s\r\n", payload->valuestring);
			return -1;
		}
		//cJSON_Delete(mqtt_t->root); //释放内存
	}
	return 0;
}