#include <wangyonglin/config.h>
#include <wangyonglin/core.h>

int wangyonglin_system_init(const char *filename, int daemon)
{
    if (wangyonglin_conf_setting(filename) != 0)
        return -1;

    if (wangyonglin_pid_init("pid") != 0)
        return -2;
    if (wangyonglin_logger_init("access_log", "error_log") != 0)
        return -3;
    if (daemon == 1)
    {
        wangyonglin_daemon();
    }
    return 0;
}
struct tm *wangyonglin_core_localtime()
{
    time_t time_seconds = time(0);
    struct tm *now_time = localtime(&time_seconds);
    now_time->tm_year += 1900;
    now_time->tm_mon += 1;
    return now_time;
}
