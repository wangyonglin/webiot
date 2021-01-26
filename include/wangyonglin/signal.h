
#ifndef _WANGYONGLIN_SIGNAL_H_INCLUDE_
#define _WANGYONGLIN_SIGNAL_H_INCLUDE_
#include <wangyonglin/config.h>
#include <wangyonglin/core.h>

typedef struct wangyonglin_signal_s wangyonglin_signal_t;

struct wangyonglin_signal_s
{
    struct sigaction act;
    int signo;
    union sigval sval;
};

void new_op(int, siginfo_t *, void *);
void wangyonglin_signal_action(wangyonglin_signal_t *signal_t,int signo);
void wangyonglin_signal_queue(wangyonglin_signal_t *signal_t,int sival_int, char *sival_ptr);
#endif