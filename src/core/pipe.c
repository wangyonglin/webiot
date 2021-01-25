#include <wangyonglin/config.h>
#include <wangyonglin/core.h>
void wangyonglin_pipe_callbacl(void *arg);
int wangyonglin_pipe_create(wangyonglin_pipe_t *pipe_t)
{
    int rc = -1;
    if ((rc = pipe(pipe_t->fd)) == -1)
    {
        wangyonglin_error_perror("wangyonglin_pipe_create\n");
        return rc;
    }
    return rc;
}
ssize_t wangyonglin_pipe_write(wangyonglin_pipe_t *pipe, unsigned char *data, size_t len)
{
    return write(pipe->fd[1], data, len);
}
ssize_t wangyonglin_pipe_read(wangyonglin_pipe_t *pipe, unsigned char *data, size_t len)
{
    return read(pipe->fd[0], data, len);
}
ssize_t wangyonglin_pipe_pthread(wangyonglin_pipe_t *pipe)
{
    pthread_t id;
    pthread_create(&id, NULL, wangyonglin_pipe_callbacl, pipe);
    return 3;
}
void wangyonglin_pipe_callbacl(void *arg)
{
    wangyonglin_pipe_t *pipe = (wangyonglin_pipe_t *)arg;
   //return read(pipe->fd[0], data, len);
}
