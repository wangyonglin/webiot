
#include <wangyonglin/config.h>
#include <wangyonglin/core.h>

  struct tm * wangyonglin_time_now(){
    time_t time_seconds = time(0);
    struct tm* now_time = localtime(&time_seconds);
    now_time->tm_year += 1900;
    now_time->tm_mon += 1;
    return now_time;
}