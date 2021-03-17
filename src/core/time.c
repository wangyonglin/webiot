#include <wangyonglin/config.h>
#include <wangyonglin/core.h>


void wangyonglin_localtime_timestamp(char *buf)
{

    time_t time_seconds = time(0);
    struct tm *t = localtime(&time_seconds);
    t->tm_year += 1900;
    t->tm_mon += 1;
    sprintf(buf, "%04d-%02d-%02dT%02d:%02d:%02dZ", t->tm_year, t->tm_mon, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
}
