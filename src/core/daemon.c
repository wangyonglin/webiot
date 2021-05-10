#include <wangyonglin/linux.h>
#include <wangyonglin/wangyonglin.h>

int wangyonglin__daemon(struct wangyonglin__config *config)
{
    if(!config->daemon) return ERR_SUCCESS;
    int fd;
    switch (fork())
    {
    case -1:
        wangyonglin__logger(config, LOG_ERR, "fork() failed");
        return ERR_DAEMON;

    case 0:
        break;

    default:
        exit(0);
    }
    if ((chdir("/")) < 0)
    {
        wangyonglin__logger(config, LOG_ERR, "could change to root dir");
         return ERR_DAEMON;
    }
    if (setsid() == -1)
    {
        wangyonglin__logger(config, LOG_ERR, "\t\tsetsid() failed");
          return ERR_DAEMON;
    }
    umask(0);

    fd = open("/dev/null", O_RDWR);
    if (fd == -1)
    {
        wangyonglin__logger(config, LOG_ERR, "open(\"/dev/null\") failed");
          return ERR_DAEMON;
    }

    if (dup2(fd, STDIN_FILENO) == -1)
    {
        wangyonglin__logger(config, LOG_ERR, "dup2(STDIN) failed");
          return ERR_DAEMON;
    }

    if (dup2(fd, STDOUT_FILENO) == -1)
    {
        wangyonglin__logger(config, LOG_ERR, "dup2(STDOUT) failed");
          return ERR_DAEMON;
    }
    if (fd > STDERR_FILENO)
    {
        if (close(fd) == -1)
        {
            wangyonglin__logger(config, LOG_ERR, "close() failed");
             return ERR_DAEMON;
        }
    }
    config->pid=getpid();
    return ERR_SUCCESS;
}