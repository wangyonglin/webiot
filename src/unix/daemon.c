#include <wangyonglin/config.h>
#include <wangyonglin/core.h>

pid_t unix_daemon(){
    pid_t pid;int fd;
    switch (fork()) {
    case -1:
        wangyonglin_log_error(LOG_EMERG,"fork() failed");
        exit(EXIT_FAILURE);

    case 0:
        break;

    default:
        exit(0);
    }

    pid = getpid();
    if ((chdir("/")) < 0) {
        wangyonglin_log_error(LOG_EMERG, "could change to root dir!");
        exit(EXIT_FAILURE);
    }
    if (setsid() == -1) {
        wangyonglin_log_error(LOG_EMERG,"setsid() failed");
        exit(EXIT_FAILURE);
    }
     umask(0);

    fd = open("/dev/null", O_RDWR);
    if (fd == -1) {
        wangyonglin_log_error(LOG_EMERG,"open(\"/dev/null\") failed");
       exit(EXIT_FAILURE);
    }

    if (dup2(fd, STDIN_FILENO) == -1) {
        wangyonglin_log_error(LOG_EMERG, "dup2(STDIN) failed");
       exit(EXIT_FAILURE);
    }

    if (dup2(fd, STDOUT_FILENO) == -1) {
        wangyonglin_log_error(LOG_EMERG, "dup2(STDOUT) failed");
        exit(EXIT_FAILURE);
    }

#if 0
    if (dup2(fd, STDERR_FILENO) == -1) {
        ngx_log_error(NGX_LOG_EMERG, log, ngx_errno, "dup2(STDERR) failed");
        return NGX_ERROR;
    }
#endif

    if (fd > STDERR_FILENO) {
        if (close(fd) == -1) {
            wangyonglin_log_error(LOG_EMERG, "close() failed");
           exit(EXIT_FAILURE);
        }
    }

    return pid;
}   