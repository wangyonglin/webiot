#include <wangyonglin/linux.h>
#include <wangyonglin/wangyonglin.h>

time_t timeify_time(void)
{

    return time(NULL);
}
int timeify_timestamp(configify_t *config, char *strout,int sizeout)
{
    char log_line[1000];
    time_t rawtime;
    struct tm *info;
    time(&rawtime);
    info = localtime(&rawtime);
    return strftime(strout, sizeout, config->log_timestamp_format, info);
}