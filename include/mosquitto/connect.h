#ifndef INCLUDE_MOSQUITTO_CONNECT_H
#define INCLUDE_MOSQUITTO_CONNECT_H
#include <wangyonglin/linux.h>
#include <wangyonglin/wangyonglin.h>
#include <mosquitto.h>
#include <mosquitto/mosquitto.h>
void connect__callback(struct mosquitto *mosq, void *obj, int rc);
#endif