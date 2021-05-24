#ifndef INCLUDE_MOSQUITTO_DISCONNECT_H
#define INCLUDE_MOSQUITTO_DISCONNECT_H
#include <wangyonglin/linux.h>
#include <wangyonglin/wangyonglin.h>
#include <mosquitto.h>
#include <mosquitto/mosquitto.h>
void disconnect__callback(struct mosquitto *mosq, void *obj, int rc);
#endif