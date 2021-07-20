#include <wangyonglin/linux.h>
#include <wangyonglin/wangyonglin.h>

struct wangyonglin__config *wangyonglin__config_new()
{

    struct wangyonglin__config *config = (struct wangyonglin__config *)malloc(sizeof(struct wangyonglin__config));
    memset(config, 0, sizeof(config));

    config->daemon = true;
    if (config->log_fptr)
    {
        fclose(config->log_fptr);
        config->log_fptr = NULL;
    }
    wangyonglin__free(config->log_file);
    config->log_file = NULL;
    config->log_timestamp_format = "%Y-%m-%d %H:%M:%S";
    config->log_timestamp = true;
    config->pid = getpid();

    return config;
}
void wangyonglin__config_cleanup(struct wangyonglin__config *config_t)
{
    wangyonglin__free(config_t);
    config_t = NULL;
}
int wangyonglin__config_load(struct wangyonglin__config *config,const char *filename)
{
    char errbuf[200];
    FILE *fd;
    fd = fopen(filename, "r");
    if (fd == NULL)
    {
        fprintf(stderr, "this is log file not find");
        return ERR_CONFIG;
    }
    config->conf = wangyonglin_conf_parse_file(fd, errbuf, sizeof(errbuf));
    if (config->conf == NULL)
        return ERR_CONFIG;
    //读取系统配置文件的内容
    wangyonglin_conf_table_t *system = wangyonglin_conf_table_in(config->conf, "SYSTEM");
    if (!system)
    {
        fprintf(stderr, "missing [SYSTEM]\n");
        return ERR_CONFIG;
    }
    wangyonglin_conf_datum_t pid = wangyonglin_conf_string_in(system, "pid");
    if (!pid.ok)
    {
        fprintf(stderr, "cannot read SYSTEM.pid", "");
        return ERR_CONFIG;
    }
    else
    {
        config->pid_file = pid.u.s;
    }
    wangyonglin_conf_datum_t log = wangyonglin_conf_string_in(system, "log");
    if (!log.ok)
    {
        fprintf(stderr, "cannot read wangyonglin.log", "");
        return ERR_CONFIG;
    }
    else
    {
        config->log_file = log.u.s;
    }
    wangyonglin_conf_datum_t user = wangyonglin_conf_string_in(system, "user");
    if (!user.ok)
    {
        fprintf(stderr, "cannot read wangyonglin.log", "");
        return ERR_CONFIG;
    }
    else
    {
        config->user = user.u.s;
    }

    wangyonglin_conf_datum_t group = wangyonglin_conf_string_in(system, "group");
    if (!group.ok)
    {
        fprintf(stderr, "cannot read wangyonglin.log", "");
        return ERR_CONFIG;
    }
    else
    {
        config->group = group.u.s;
    }

    if (fd)
    {
        fclose(fd);
    }

    return ERR_SUCCESS;
}

