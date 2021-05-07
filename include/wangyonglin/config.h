#ifndef INCLUDE_WANGYONGLIN_CONFIG_H
#define INCLUDE_WANGYONGLIN_CONFIG_H
#include <wangyonglin/linux.h>
#include <wangyonglin/wangyonglin.h>
typedef struct wangyonglin__config wangyonglin__config_t;

struct wangyonglin__config
{
    bool daemon;
    pid_t pid;
    char *pid_file;
    unsigned int log_dest;
    int log_facility;
    unsigned int log_type;
    bool log_timestamp;
    char *log_timestamp_format;
    char *log_file;
    FILE *log_fptr;
    char *user;
    char *group;
    wangyonglin_conf_table_t *conf;
    struct wangyonglin__signal *signal;
};

struct wangyonglin__config *config__new();
void config__cleanup(struct wangyonglin__config *config);
int config__load(struct wangyonglin__config *config, int argc, char *argv[]);
#endif