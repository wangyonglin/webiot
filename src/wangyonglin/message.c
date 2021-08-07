#include <wangyonglin/linux.h>
#include <wangyonglin/wangyonglin.h>
void msgify_init(configify_t *config ,msgify_t *message)
{
    if (config != NULL)
    {
        message->config = config;
    }
}

void msgify_sigaction(msgify_t *message, int signo, void (*callback)(int, siginfo_t *, void *))
{
    configify_t *config = message->config;
    sigemptyset(&message->act.sa_mask);
    message->act.sa_sigaction = callback;
    message->act.sa_flags = SA_SIGINFO;
 
    if (sigaction(signo, &message->act, NULL) < 0)

    {
        logify_printf(config, LOG_ERR, "sigal sigaction error");
        return;
    }
    return;
}
void msgify_sigqueue(msgify_t *message, int signo,int sival_int, void *sival_ptr)
{
    configify_t *config = message->config;
    message->act.sa_flags = SA_SIGINFO;
    message->sval.sival_int = sival_int;
    message->sval.sival_ptr = sival_ptr;
    //向本进程发送信号，并传递附加信息
    if (sigqueue(config->pid, signo, message->sval) < 0)
    {
        logify_printf(config, LOG_ERR, "pid %d sigal sigqueue error", config->pid);
        return;
    }
    return;
}
