#include <wangyonglin/config.h>
#include <wangyonglin/core.h>

void wangyonglin_pid_conf(wangyonglin_pid_t * pid)
{
  wangyonglin_conf_get(pid->name,"pid:pid",wangyonglin_type_string);
}
int wangyonglin_pid_init(wangyonglin_pid_t *pid)
{
    int pid_fd;
    if (pid->name != NULL)
    {
        char str[256];
        pid_fd = open(pid->name, O_RDWR | O_CREAT, 0640);
        if (pid_fd < 0)
        {
            fprintf(stderr, "Fail to open file!\n");
            exit(EXIT_FAILURE);
        }
        if (lockf(pid_fd, F_TLOCK, 0) < 0)
        {
            fprintf(stderr, "Fail to lockf file!\n");
            exit(EXIT_FAILURE);
        }
        // get pid & save in str
        sprintf(str, "%d\n", getpid());
        // write to pid file
        ssize_t ret = write(pid_fd, str, strlen(str));
        if (ret < 0)
            exit(EXIT_FAILURE);
    }
    return pid_fd;
}