#include <wangyonglin/linux_config.h>
#include <wangyonglin/wangyonglin.h>

time_t wangyonglin__time(void)
{

    return time(NULL);
}
int time__timestamp(struct wangyonglin__config *config, char *strout,int sizeout)
{
    char log_line[1000];
    time_t rawtime;
    struct tm *info;
    time(&rawtime);
    info = localtime(&rawtime);
    return strftime(strout, sizeout, config->log_timestamp_format, info);
}