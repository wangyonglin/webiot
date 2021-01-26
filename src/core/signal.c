#include <wangyonglin/config.h>
#include <wangyonglin/core.h>
#include <wangyonglin/signal.h>
void wangyonglin_signal_action(wangyonglin_signal_t *signal_t,int signo)
{
    signal_t->signo=signo;
    sigemptyset(&signal_t->act.sa_mask);

    signal_t->act.sa_sigaction = new_op;

    signal_t->act.sa_flags = SA_SIGINFO;

    if (sigaction(signal_t->signo, &signal_t->act, NULL) < 0)

    {

        printf("install sigal error\n");
    }
}
void wangyonglin_signal_queue(wangyonglin_signal_t *signal_t,int sival_int, char *sival_ptr)
{
    signal_t->act.sa_flags = SA_SIGINFO;
    signal_t->sval.sival_int=sival_int;
    signal_t->sval.sival_ptr = sival_ptr;
    //向本进程发送信号，并传递附加信息
    if (sigqueue(getpid(), signal_t->signo, signal_t->sval) < 0)
    {
        printf("install sigal error\n");
    }
}
void new_op(int signum,siginfo_t *s_t,void *p)

{

        int myint = 0;
        printf("recv signum : %d \n", signum);
        myint = s_t->si_value.sival_int;
        printf("%d, %d \n", myint, s_t->si_int );
        printf("%s, %s \n", (char *)s_t->si_value.sival_ptr, (char *)s_t->si_ptr );

}
