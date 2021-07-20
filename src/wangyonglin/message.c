#include <wangyonglin/linux.h>
#include <wangyonglin/wangyonglin.h>
void wangyonglin__message_new(struct wangyonglin__message *message, struct wangyonglin__config *config)
{
    if (config != NULL)
    {
        message->config = config;
    }
}

void wangyonglin__message_sigaction(struct wangyonglin__message *message, int signo, void (*callback)(int, siginfo_t *, void *))
{
    struct wangyonglin__config *config = message->config;
    sigemptyset(&message->act.sa_mask);
    message->act.sa_sigaction = callback;
    message->act.sa_flags = SA_SIGINFO;
 
    if (sigaction(signo, &message->act, NULL) < 0)

    {
        wangyonglin__logger(config, LOG_ERR, "sigal sigaction error");
        return;
    }
    return;
}
void wangyonglin__message_sigqueue(struct wangyonglin__message *message, int signo,int sival_int, void *sival_ptr)
{
    struct wangyonglin__config *config = message->config;
    message->act.sa_flags = SA_SIGINFO;
    message->sval.sival_int = sival_int;
    message->sval.sival_ptr = sival_ptr;
    //向本进程发送信号，并传递附加信息
    if (sigqueue(config->pid, signo, message->sval) < 0)
    {
        wangyonglin__logger(config, LOG_ERR, "pid %d sigal sigqueue error", config->pid);
        return;
    }
    return;
}
