#ifndef INCLUDE_WANGYONGLIN_MESSAGE_H
#define INCLUDE_WANGYONGLIN_MESSAGE_H
#include <wangyonglin/linux.h>
#include <wangyonglin/wangyonglin.h>

typedef struct wangyonglin__message wangyonglin__message_t;
struct wangyonglin__message
{
    struct sigaction act;
    union sigval sval;
    int signo;
    void (*callback)(int, siginfo_t *, void *);
    struct wangyonglin__config *config;
};

void wangyonglin__message_sigaction(struct wangyonglin__message *message, int signo, void (*callback)(int, siginfo_t *, void *));
void wangyonglin__message_sigqueue(struct wangyonglin__message *message, int signo, int sival_int, void *sival_ptr);
void wangyonglin__message_new(struct wangyonglin__message *message, struct wangyonglin__config *config);
#endif