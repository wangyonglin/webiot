#ifndef INCLUDE_WANGYONGLIN_MESSAGE_H
#define INCLUDE_WANGYONGLIN_MESSAGE_H
#include <wangyonglin/linux.h>
#include <wangyonglin/wangyonglin.h>

typedef struct msgify msgify_t;
struct msgify
{
    struct sigaction act;
    union sigval sval;
    int signo;
    void (*callback)(int, siginfo_t *, void *);
    configify_t *config;
};

void msgify_sigaction(msgify_t *msg, int signo, void (*callback)(int, siginfo_t *, void *));
void msgify_sigqueue(msgify_t *msg, int signo, int sival_int, void *sival_ptr);
void msgify_init(configify_t *config,msgify_t *msg);
#endif