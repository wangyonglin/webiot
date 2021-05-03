#ifndef INCLUDE_MOSQUITTO_MOSQUITTO_H
#define INCLUDE_MOSQUITTO_MOSQUITTO_H
#include <wangyonglin/linux.h>
#include <wangyonglin/wangyonglin.h>

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
    wangyonglin_string_t host;
    int port;
    int keep_alive;
    int msg_max_size;
    wangyonglin_string_t clientid;
    wangyonglin_string_t username;
    wangyonglin_string_t password;
    wangyonglin_signal_t *signal_t;
    struct mosquitto *mosq;
    struct wangyonglin__config *config;
};
struct wangyonglin_mosquitto_publish_s
{
    struct wangyonglin__config *config;
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
int mosquitto__appcation(struct wangyonglin__config *config, wangyonglin_signal_t *signal_t);
int mosquitto__publist(struct wangyonglin__config *config, const char *topic, char *payload, int payloadlen);
#endif /**_MOSQUITTO_MOSQUITTO_H_INCLUDE_**/