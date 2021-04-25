#ifndef _WANGYONGLIN_PIPE_H_INCLUDE_
#define _WANGYONGLIN_PIPE_H_INCLUDE_
#include <wangyonglin/linux_config.h>
#include <wangyonglin/wangyonglin.h>

typedef struct wangyonglin_pipe_s wangyonglin_pipe_t;
typedef int wangyonglin_pipe_fd_t;
struct wangyonglin_pipe_s
{
    wangyonglin_pipe_fd_t fd[2];
};

int wangyonglin_pipe_create(wangyonglin_pipe_t *pipe_t);
ssize_t wangyonglin_pipe_write(wangyonglin_pipe_t *pipe, unsigned char *data, size_t len);
ssize_t wangyonglin_pipe_read(wangyonglin_pipe_t *pipe, unsigned char *data, size_t len);
#endif
