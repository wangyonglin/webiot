#include <wangyonglin/config.h>
#include <wangyonglin/core.h>

wangyonglin_core_t *wangyonglin(int argc, char *argv[])
{
    wangyonglin_pid_t pid;
    wangyonglin_log_t log;
    wangyonglin_conf_init("/usr/local/wangyonglin/conf/wangyonglin.conf");
    wangyonglin_pid_conf(&pid);
    wangyonglin_pid_init(&pid);
    wangyonglin_log_conf(&log);
    wangyonglin_log_init(&log);
   // wangyonglin_daemon();
    wangyonglin_core_t core;
    return &core;
}
struct tm *wangyonglin_core_localtime()
{
    time_t time_seconds = time(0);
    struct tm *now_time = localtime(&time_seconds);
    now_time->tm_year += 1900;
    now_time->tm_mon += 1;
    return now_time;
}
