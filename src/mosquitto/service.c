#include <wangyonglin/config.h>
#include <wangyonglin/core.h>
#include <mosquitto.h>
#include <mosquitto/conf.h>
#include <mosquitto/service.h>



void wangyonglin_connect_callback(struct mosquitto *mosq, void *obj, int rc)
{
        printf("Call the function: my_connect_callback\n");

}

void wangyonglin_disconnect_callback(struct mosquitto *mosq, void *obj, int rc)
{
        printf("Call the function: my_disconnect_callback\n");
     
}

void wangyonglin_publish_callback(struct mosquitto *mosq, void *obj, int mid)
{
        printf("Call the function: my_publish_callback\n");

}


void wangyonglin_mosquitto_start(){
    wangyonglin_mosquitto_conf_t conf;
	wangyonglin_mosquitto_conf_init(&conf);
    int msglen = conf.msg_max_size;
        int ret;
        struct mosquitto *mosq;
		char buff[msglen];
		
		//初始化libmosquitto库
        ret = mosquitto_lib_init();
        if(ret){
                printf("Init lib error!\n");
                return -1;
        }
		//创建一个发布端实例
        mosq =  mosquitto_new("wangyonglin", true, NULL);
        if(mosq == NULL){
                printf("New pub_test error!\n");
                mosquitto_lib_cleanup();
                return -1;
        }

		//设置回调函数
        mosquitto_connect_callback_set(mosq, wangyonglin_connect_callback);
		mosquitto_disconnect_callback_set(mosq, wangyonglin_disconnect_callback);
        mosquitto_publish_callback_set(mosq, wangyonglin_publish_callback);

		// 连接至服务器
        // 参数：句柄、ip（host）、端口、心跳
        ret = mosquitto_connect(mosq, conf.host, conf.port, conf.keep_alive);
        if(ret){
                printf("Connect server error!\n");
                mosquitto_destroy(mosq);
                mosquitto_lib_cleanup();
                return -1;
        }

        printf("Start!\n");
		
        //mosquitto_loop_start作用是开启一个线程，在线程里不停的调用 mosquitto_loop() 来处理网络信息
		
		int loop = mosquitto_loop_start(mosq); 
		if(loop != MOSQ_ERR_SUCCESS)
		{
			printf("mosquitto loop error\n");
			return 1;
		}


		while(fgets(buff, msglen, stdin) != NULL)
		{
			/*发布消息*/
			mosquitto_publish(mosq,NULL,"wangyonglin",strlen(buff)+1,buff,0,0);
			memset(buff,0,sizeof(buff));
		}

        mosquitto_destroy(mosq);
        mosquitto_lib_cleanup();
        printf("End!\n");

        return 0;
}