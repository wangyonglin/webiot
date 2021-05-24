#ifndef INCLUDE_MOSQUITTO_MESSAGE_H
#define INCLUDE_MOSQUITTO_MESSAGE_H
#include <wangyonglin/linux.h>
#include <wangyonglin/wangyonglin.h>
#include <mosquitto.h>
#include <mosquitto/mosquitto.h>
void message__callback(struct mosquitto *mosq, void *obj, const struct mosquitto_message *msg);
#endif