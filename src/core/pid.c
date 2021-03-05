#include <wangyonglin/config.h>
#include <wangyonglin/core.h>


int wangyonglin_pid_init(const char *section)
{
    wangyonglin_string_t string_t = wangyonglin_null_string;
    string_t = wangyonglin_conf_string(section);

    int pid_fd;
    if (string_t.data != NULL)
    {
        char str[256];
        pid_fd = open(string_t.data, O_RDWR | O_CREAT, 0640);
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
    return 0;
}