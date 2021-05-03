
#ifndef INCLUDE_WANGYONGLIN_SIGNAL_H
#define INCLUDE_WANGYONGLIN_SIGNAL_H
#include <wangyonglin/linux.h>
#include <wangyonglin/wangyonglin.h>

typedef struct wangyonglin_signal_s wangyonglin_signal_t;

struct wangyonglin_signal_s
{
    pid_t pid;
    struct sigaction act;
    union sigval sval;
};

typedef void (*wangyonglin_signal_callback_t)(int, siginfo_t *, void *);
void wangyonglin_signal_action(wangyonglin_signal_t *signal_t,int signo,wangyonglin_signal_callback_t * call);
void wangyonglin_signal_queue(wangyonglin_signal_t *signal_t,int signo,int sival_int, void *sival_ptr);
#endif