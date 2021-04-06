#include <wangyonglin/config.h>
#include <wangyonglin/core.h>

struct tm *wangyonglin_logger_timenow();
int wangyonglin_logger__fileexists(char *filename);

wangyonglin_string_t access_log_t = wangyonglin_null_string;
wangyonglin_string_t error_log_t = wangyonglin_null_string;
int wangyonglin_logger_init(wangyonglin_conf_table_t *conf)
{

    //读取系统配置文件的内容
    wangyonglin_conf_table_t *system = wangyonglin_conf_table_in(conf, "SYSTEM");
    if (!system)
    {
        fprintf(stderr, "missing [SYSTEM]\n");
        exit(EXIT_FAILURE);
    }
    wangyonglin_conf_datum_t access = wangyonglin_conf_string_in(system, "access");
    if (!access.ok)
    {
        fprintf(stderr, "cannot read SYSTEM.access", "");
        exit(EXIT_FAILURE);
    }
    wangyonglin_conf_datum_t error = wangyonglin_conf_string_in(system, "error");
    if (!error.ok)
    {
        fprintf(stderr, "cannot read SYSTEM.error", "");
        exit(EXIT_FAILURE);
    }
  //  fprintf(stdout, "\t%s\r\n", access.u.s);
   // fprintf(stdout, "\t%s\r\n", error.u.s);
    wangyonglin_string_setting(&access_log_t, access.u.s);
    wangyonglin_string_setting(&error_log_t, error.u.s);
  //  free(access.u.s);
  //  free(error.u.s);
    return 0;
}

void wangyonglin_logger_success(const char *format, ...)
{

    if (access_log_t.data == NULL)
    {
        fprintf(stderr, "logs->access_log : not null \n");
        exit(EXIT_FAILURE);
    }

    if (wangyonglin_logger__fileexists(access_log_t.data) == 0)
    {
        fprintf(stderr, "it not exists : %s \n", access_log_t.data);
        exit(EXIT_FAILURE);
    }
    else
    {
        int ret = open(access_log_t.data, O_RDWR | O_CREAT, 0640);
        if (ret != -1)
        {
            close(ret);
        }
    }

    FILE *fd = fopen(access_log_t.data, "a");
    if (fd == NULL)
    {
        fprintf(stderr, "it open fait : %s \n", access_log_t.data);
        exit(EXIT_FAILURE);
    }

    struct tm *t;
    t = wangyonglin_logger_timenow();
    va_list args;
    va_start(args, format);

    fprintf(fd, "%04d-%02d-%02d %02d:%02d:%02d\t", t->tm_year, t->tm_mon, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
    vfprintf(fd, format, args);
    fputc('\r', fd);
    fputc('\n', fd);
    fflush(fd);
    va_end(args);
    fclose(fd);
}

void wangyonglin_logger_failure(const char *format, ...)
{
    if (access(error_log_t.data, F_OK) != 0)
    {
        fprintf(stderr, "\tlog error %s %s \n", error_log_t.data, strerror(errno));
        return;
    }

    struct tm *t;

    if (wangyonglin_logger__fileexists(error_log_t.data) == 0)
    {
        fprintf(stderr, "it not exists : %s \n", error_log_t.data);
        exit(EXIT_FAILURE);
    }
    else
    {
        int ret = open(error_log_t.data, O_RDWR | O_CREAT, 0640);
        if (ret != -1)
        {
            close(ret);
        }
    }

    FILE *fd = fopen(error_log_t.data, "a+");
    if (fd == NULL)
    {
        fprintf(stderr, "it open fait : %s \n", error_log_t.data);
        exit(-1);
    }
    t = wangyonglin_logger_timenow();
    va_list args;
    va_start(args, format);

    fprintf(fd, "%04d-%02d-%02d %02d:%02d:%02d\t", t->tm_year, t->tm_mon, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
    fprintf(fd, "%s\t", "ERROR");
    vfprintf(fd, format, args);
    fputc('\r', fd);
    fputc('\n', fd);
    fflush(fd);
    va_end(args);
    fclose(fd);
}
struct tm *wangyonglin_logger_timenow()
{
    time_t time_seconds = time(0);
    struct tm *now_time = localtime(&time_seconds);
    now_time->tm_year += 1900;
    now_time->tm_mon += 1;
    return now_time;
}
int wangyonglin_logger__fileexists(char *filename)
{
    return (access(filename, 0) == 0);
}
