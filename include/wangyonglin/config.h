#ifndef _CONFIG_H_INCLUDE_
#define _CONFIG_H_INCLUDE_
#include <wangyonglin/linux_config.h>
#include <wangyonglin/wangyonglin.h>
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
    wangyonglin_conf_table_t *conf;
};

void config__init(struct wangyonglin__config *config);
void config__cleanup(struct wangyonglin__config *config);
int config__load(struct wangyonglin__config *config, int argc, char *argv[]);
#endif