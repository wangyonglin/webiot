#ifndef INCLUDE_WANGYONGLIN_CORE_H
#define INCLUDE_WANGYONGLIN_CORE_H
#include <wangyonglin/linux.h>
#include <wangyonglin/wangyonglin.h>
int application(struct wangyonglin__config *config);
#ifndef WANGYONGLIN__CALL
#define WANGYONGLIN__CALL
typedef struct wangyonglin__call wangyonglin__call_t;
struct wangyonglin__call
{
    void *(*app)(struct wangyonglin__config *config, void *args);
    //struct wangyonglin__config *config;
};
#endif

typedef struct wangyonglin__executable wangyonglin__executable_t;
struct wangyonglin__executable
{
    struct stat st;
    DIR *dir;
    struct dirent *dirent;
    char *process;
};
size_t wangyonglin__executable(struct wangyonglin__config *config);
#endif
