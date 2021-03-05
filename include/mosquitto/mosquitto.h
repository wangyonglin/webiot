#ifndef _MOSQUITTO_MOSQUITTO_H_INCLUDE_
#define _MOSQUITTO_MOSQUITTO_H_INCLUDE_
#include <wangyonglin/config.h>
#include <wangyonglin/core.h>

typedef struct wangyonglin_mosquitto_s wangyonglin_mosquitto_t;
typedef struct wangyonglin_mosquitto_conf_s wangyonglin_mosquitto_conf_t;
typedef struct wangyonglin_mosquitto_publish_s wangyonglin_mosquitto_publish_t;
typedef struct wangyonglin_mosquitto_user_s wangyonglin_mosquitto_user_t;

struct wangyonglin_mosquitto_conf_s
{
    wangyonglin_string_t host;
    int port;
    int keep_alive;
    int msg_max_size;
};

struct wangyonglin_mosquitto_s
{
    pthread_t pid;
    wangyonglin_mosquitto_conf_t *conf_t;
    wangyonglin_mosquitto_user_t *user_t;
    wangyonglin_signal_t *signal_t;
    struct mosquitto *mosq;
};
struct wangyonglin_mosquitto_publish_s
{
    wangyonglin_mosquitto_t *mosquitto_t;
    wangyonglin_string_t topic;
    wangyonglin_string_t payload;
};
struct wangyonglin_mosquitto_user_s
{
    wangyonglin_string_t clientid;
    wangyonglin_string_t username;
    wangyonglin_string_t password;
};

void wangyonglin_mosquitto_create();
int wangyonglin_mosquitto_appcation(wangyonglin_signal_t *signal_t);
void wangyonglin_mosquitto_publist(const char* topic,char* payload,int payloadlen);
#endif /**_MOSQUITTO_MOSQUITTO_H_INCLUDE_**/