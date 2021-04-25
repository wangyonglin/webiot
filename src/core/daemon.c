#include <wangyonglin/linux_config.h>
#include <wangyonglin/wangyonglin.h>

pid_t wangyonglin__daemonise(struct wangyonglin__config *config)
{
    pid_t pid;
    int fd;
    switch (fork())
    {
    case -1:
        log__printf(config, LOG_ERR, "fork() failed");
        exit(EXIT_FAILURE);

    case 0:
        break;

    default:
        exit(0);
    }

    pid = getpid();
    if ((chdir("/")) < 0)
    {
        log__printf(config, LOG_ERR, "could change to root dir");
        exit(EXIT_FAILURE);
    }
    if (setsid() == -1)
    {
        log__printf(config, LOG_ERR, "\t\tsetsid() failed");
        exit(EXIT_FAILURE);
    }
    umask(0);

    fd = open("/dev/null", O_RDWR);
    if (fd == -1)
    {
        log__printf(config, LOG_ERR, "open(\"/dev/null\") failed");
        exit(EXIT_FAILURE);
    }

    if (dup2(fd, STDIN_FILENO) == -1)
    {
        log__printf(config, LOG_ERR, "dup2(STDIN) failed");
        exit(EXIT_FAILURE);
    }

    if (dup2(fd, STDOUT_FILENO) == -1)
    {
        log__printf(config, LOG_ERR, "dup2(STDOUT) failed");
        exit(EXIT_FAILURE);
    }
    if (fd > STDERR_FILENO)
    {
        if (close(fd) == -1)
        {
            log__printf(config, LOG_ERR, "close() failed");
            exit(EXIT_FAILURE);
        }
    }

    return pid;
}