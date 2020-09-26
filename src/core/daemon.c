#include <wangyonglin/config.h>
#include <wangyonglin/core.h>

pid_t wangyonglin_daemon(){
    pid_t pid;int fd;
    switch (fork()) {
    case -1:
       fprintf(stderr,"\t\tfork() failed\n");
        exit(EXIT_FAILURE);

    case 0:
        break;

    default:
        exit(0);
    }

    pid = getpid();
    if ((chdir("/")) < 0) {
       fprintf(stderr, "could change to root dir!\n");
        exit(EXIT_FAILURE);
    }
    if (setsid() == -1) {
       fprintf(stderr,"\t\tsetsid() failed\n");
        exit(EXIT_FAILURE);
    }
     umask(0);

    fd = open("/dev/null", O_RDWR);
    if (fd == -1) {
       fprintf(stderr,"\t\topen(\"/dev/null\") failed\n");
       exit(EXIT_FAILURE);
    }

    if (dup2(fd, STDIN_FILENO) == -1) {
       fprintf(stderr,"\tdup2(STDIN) failed\n");
       exit(EXIT_FAILURE);
    }

    if (dup2(fd, STDOUT_FILENO) == -1) {
       fprintf(stderr,"\tdup2(STDOUT) failed\n");
        exit(EXIT_FAILURE);
    }

#if 0
    if (dup2(fd, STDERR_FILENO) == -1) {
        ngx_log_error(NGX_LOG_EMERG, log, ngx_errno, "dup2(STDERR) failed\n");
        return NGX_ERROR;
    }
#endif

    if (fd > STDERR_FILENO) {
        if (close(fd) == -1) {
           fprintf(stderr,"\tclose() failed\n");
           exit(EXIT_FAILURE);
        }
    }

    return pid;
}   