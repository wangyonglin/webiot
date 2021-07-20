#ifndef HTTPS_CONFIG_H
#define HTTPS_CONFIG_H

#include <wangyonglin/linux.h>
#include <wangyonglin/wangyonglin.h>

typedef struct https__config https_config_t;

struct https__config
{
    int port;
    int backlog;
    int threads;
    const char *certificate_chain;
    const char *private_key;
};

void https__config_init(struct wangyonglin__config *config, struct https__config *config_t);
#endif