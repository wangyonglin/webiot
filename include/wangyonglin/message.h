#ifndef INCLUDE_WANGYONGLIN_MESSAGE_H
#define INCLUDE_WANGYONGLIN_MESSAGE_H
#include <wangyonglin/linux.h>
#include <wangyonglin/wangyonglin.h>
void message__new(struct wangyonglin__config *config, int signo, void (*callback_t)(int, siginfo_t *, void *));
void message__send(struct wangyonglin__config *config, int signo, int sival_int, void *sival_ptr);
#endif