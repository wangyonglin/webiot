#include <wangyonglin/linux.h>
#include <wangyonglin/wangyonglin.h>


void message__new(struct wangyonglin__config *config, int signo, void (*callback_t)(int, siginfo_t *, void *))
{
    struct wangyonglin__signal *signal_t = config->signal;
    sigemptyset(&signal_t->act.sa_mask);
    signal_t->act.sa_sigaction = callback_t;
    signal_t->act.sa_flags = SA_SIGINFO;
    if (sigaction(signo, &signal_t->act, NULL) < 0)

    {
        log__printf(config, LOG_ERR, "sigal sigaction error");
        return;
    }
    return;
}
void message__send(struct wangyonglin__config *config, int signo, int sival_int, void *sival_ptr)
{
    struct wangyonglin__signal *signal_t = config->signal;
    signal_t->act.sa_flags = SA_SIGINFO;
    signal_t->sval.sival_int = sival_int;
    signal_t->sval.sival_ptr = sival_ptr;
    //向本进程发送信号，并传递附加信息
    if (sigqueue(config->pid, signo, signal_t->sval) < 0)
    {
        log__printf(config, LOG_ERR, "pid %d sigal sigqueue error",config->pid);
        return;
    }
    return;
}