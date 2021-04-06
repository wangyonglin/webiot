#include <wangyonglin/config.h>
#include <wangyonglin/core.h>

wangyonglin_conf_table_t* wangyonglin_application_initialization(const char *file, int daemon)
{
    FILE *fp;
    char errbuf[200];

    // 1. Read and parse conf file
    fp = fopen(file, "r");
    if (!fp)
    {
        fprintf(stderr, "cannot open wangyonglin.conf - ", strerror(errno));
        exit(EXIT_FAILURE);
    }
    wangyonglin_conf_table_t *conf = wangyonglin_conf_parse_file(fp, errbuf, sizeof(errbuf));
    fclose(fp);

    if (wangyonglin_pid_init(conf) != 0)
        return NULL;
    if (wangyonglin_logger_init(conf) != 0)
        return NULL;
    if (daemon == 1)
    {
        wangyonglin_daemon();
    }
    return conf;
}
struct tm *wangyonglin_core_localtime()
{
    time_t time_seconds = time(0);
    struct tm *now_time = localtime(&time_seconds);
    now_time->tm_year += 1900;
    now_time->tm_mon += 1;
    return now_time;
}
