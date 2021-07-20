#include <wangyonglin/linux.h>
#include <wangyonglin/wangyonglin.h>

int wangyonglin__log_init(struct wangyonglin__config *config)
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
int wangyonglin__log_close(struct wangyonglin__config *config)
{
    if (config->log_fptr)
    {
        fclose(config->log_fptr);
    }
}

int wangyonglin__log_printf(struct wangyonglin__config *config, unsigned int priority, const char *fmt, ...)
{
    va_list va;
    int rc;
    va_start(va, fmt);
    rc = wangyonglin__log_vprintf(config, priority, fmt, va);
    va_end(va);
    return rc;
}

int wangyonglin__log_vprintf(struct wangyonglin__config *config, unsigned int priority, const char *fmt, va_list va)
{
    char log_line[1000];
    size_t log_line_pos;

    if (config->log_timestamp)
    {
        time_t rawtime;
        struct tm *info;
        time(&rawtime);
        info = localtime(&rawtime);
        log_line_pos = strftime(log_line, sizeof(log_line), config->log_timestamp_format, info);

        if (config->log_fptr)
        {

            fprintf(config->log_fptr, log_line);
            switch (priority)
            {
            case LOG_ERR:
                fprintf(config->log_fptr, "%s\t", " ERROR : ");
                break;
            case LOG_INFO:
                fprintf(config->log_fptr, "%s\t", " INFO :  ");
                break;
            case LOG_DEBUG:
                fprintf(config->log_fptr, "%s\t", " DEBUF : ");
                break;
            default:
                fprintf(config->log_fptr, "%s\t", " NONE :  ");
                break;
            }
            vfprintf(config->log_fptr, fmt, va);
            fputc('\r', config->log_fptr);
            fputc('\n', config->log_fptr);
            fflush(config->log_fptr);
        }
        return log_line_pos;
    }
    return log_line_pos;
}