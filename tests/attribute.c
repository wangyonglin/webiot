#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include <time.h>
typedef struct wangyonglin__db wangyonglin__db_t;
typedef struct wangyonglin__config wangyonglin__config_t;

struct wangyonglin__config
{
    bool daemon;
    char *pid_file;
    unsigned int log_dest;
    int log_facility;
    unsigned int log_type;
    bool log_timestamp;
    char *log_timestamp_format;
    char *log_file;
    FILE *log_fptr;
    char *user;
};
struct wangyonglin__db
{

    time_t now_s;      /* Monotonic clock, where possible */
    time_t now_real_s; /* Read clock, for measuring session/message expiry */
    wangyonglin__config_t *config;
};
int log__vprintf(struct wangyonglin__config *config, unsigned int priority, const char *fmt, va_list va);
int log__printf(struct wangyonglin__db *db, unsigned int priority, const char *fmt, ...) __attribute__((format(printf, 3, 4)));
int log__init(struct wangyonglin__config *config)
{

    if (!config->log_file)
    {
        fprintf(stderr, "wangyonglin.conf log file not found:%s \n", config->log_file);
        return 1;
    }
    config->log_fptr = fopen(config->log_file, "a+");
    if (config->log_fptr == NULL)
    {
        fprintf(stderr, "it open fait : %s \n", config->log_file);
        return 2;
    }

    return 3;
}
int log__close(struct wangyonglin__config *config)
{
    if (config->log_fptr)
    {
        fclose(config->log_fptr);
    }
}

int log__printf(struct wangyonglin__db *db, unsigned int priority, const char *fmt, ...)
{
    va_list va;
    //UNUSED(db);
    int rc;
    va_start(va, fmt);
    rc = log__vprintf(db->config,priority, fmt, va);
    va_end(va);
    return rc;
}
int log__vprintf(struct wangyonglin__config *config, unsigned int priority, const char *fmt, va_list va)
{
    char log_line[1000];
    size_t log_line_pos;
    char *log_timestamp_format = NULL;

    if (config->log_timestamp_format)
    {
        log_timestamp_format = config->log_timestamp_format;
    }
    else
    {
        log_timestamp_format = "%Y-%m-%d %H:%M:%S";
    }

    time_t rawtime;
    struct tm *info;
    time(&rawtime);
    info = localtime(&rawtime);
    log_line_pos = strftime(log_line, sizeof(log_line), log_timestamp_format, info);
    if (log_line_pos < sizeof(log_line) - 3)
    {
        log_line[log_line_pos] = ':';
        log_line[log_line_pos + 1] = ' ';
        log_line[log_line_pos + 2] = '\0';
        log_line_pos += 2;
    }
    vsnprintf(&log_line[log_line_pos], sizeof(log_line) - log_line_pos, fmt, va);

    log_line[sizeof(log_line) - 1] = '\0'; /* Ensure string is null terminated. */
    printf(log_line);
    if(config->log_fptr){
        fprintf(config->log_fptr,log_line);
        fflush(config->log_fptr);
    }
    return log_line_pos;
}
int main(int argc, char *args[])
{

    log__printf(NULL, 2, "%s", "wangyonglin");

    return EXIT_SUCCESS;
}
