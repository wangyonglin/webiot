#include <wangyonglin/linux_config.h>
#include <wangyonglin/wangyonglin.h>

int wangyonglin__pid_write(struct wangyonglin__config *config)
{
    int pid_fd;
    if (config->pid_file != NULL)
    {

        char str[256];
        pid_fd = open(config->pid_file, O_RDWR | O_CREAT, 0640);
        if (pid_fd < 0)
        {
            log__printf(config, LOG_ERR, "Fail to open file");
            return ERR_UNKNOWN;
        }
        if (lockf(pid_fd, F_TLOCK, 0) < 0)
        {
            log__printf(config, LOG_ERR, "Fail to lockf file");
            return ERR_UNKNOWN;
        }
        // get pid & save in str
        sprintf(str, "%d\n", getpid());
        // write to pid file
        ssize_t ret = write(pid_fd, str, strlen(str));
        if (ret < 0)
            return ERR_UNKNOWN;
        close(pid_fd);
    }

    return ERR_SUCCESS;
}