#ifndef INCLUDE_MOSQUITTO_SUBSCRIBE_H
#define INCLUDE_MOSQUITTO_SUBSCRIBE_H
#include <wangyonglin/linux.h>
#include <wangyonglin/wangyonglin.h>
#include <mosquitto.h>
#include <mosquitto/mosquitto.h>
void subscribe__callback(struct mosquitto *mosq, void *obj, int mid, int qos_count, const int *granted_qos);
#endif