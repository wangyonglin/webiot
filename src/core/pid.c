#include <wangyonglin/config.h>
#include <wangyonglin/core.h>

int wangyonglin_pid_init(wangyonglin_conf_table_t *conf)
{
    int pid_fd;
    //读取系统配置文件的内容
    wangyonglin_conf_table_t *system = wangyonglin_conf_table_in(conf, "SYSTEM");
    if (!system)
    {
        fprintf(stderr, "missing [SYSTEM]\n");
        exit(EXIT_FAILURE);
    }
    wangyonglin_conf_datum_t pid = wangyonglin_conf_string_in(system, "pid");
    if (!pid.ok)
    {
        fprintf(stderr, "cannot read SYSTEM.pid", "");
        exit(EXIT_FAILURE);
    }
  
    if (pid.u.s != NULL)
    {
        char str[256];
        pid_fd = open(pid.u.s, O_RDWR | O_CREAT, 0640);
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
    free(pid.u.s);
    return 0;
}