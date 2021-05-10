#ifndef INCLUDE_WANGYONGLIN_MESSAGE_H
#define INCLUDE_WANGYONGLIN_MESSAGE_H
#include <wangyonglin/linux.h>
#include <wangyonglin/wangyonglin.h>
void wangyonglin__message_new(struct wangyonglin__config *config, int signo, void (*callback_t)(int, siginfo_t *, void *));
void wangyonglin__message_send(struct wangyonglin__config *config, int signo, int sival_int, void *sival_ptr);
#endif