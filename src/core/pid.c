#include <wangyonglin/linux.h>
#include <wangyonglin/wangyonglin.h>
/**
 * \brief Write a pid file (used at the startup)
 *        This commonly needed by the init scripts
 *
 * \param config to the name of the pid file to write (optarg)
 *
 * \retval ERR_SUCCESS if succes
 * \retval ERR_PID on failure 
 */
int wangyonglin__pid_create(struct wangyonglin__config *config)
{
    int pid_fd;
    char val[16];
    int len = snprintf(val, sizeof(val), "%" PRIuMAX "\n", (uintmax_t)config->pid);
    if (len <= 0)
    {
        wangyonglin__logger(config, LOG_ERR, "Pid error (%s)", strerror(errno));
        return ERR_PID;
    }

    char str[256];
    pid_fd = open(config->pid_file, O_CREAT | O_TRUNC | O_NOFOLLOW | O_WRONLY, 0644);
    if (pid_fd < 0)
    {
        wangyonglin__logger(config, LOG_ERR, "unable to set pidfile '%s': %s", config->pid_file, strerror(errno));
        return ERR_PID;
    }
    if (lockf(pid_fd, F_TLOCK, 0) < 0)
    {
        wangyonglin__logger(config, LOG_ERR, "unable to lockf file: %s", strerror(errno));
        return ERR_PID;
    }
    ssize_t ret = write(pid_fd, val, (unsigned int)len);
    if (ret == -1)
    {
        wangyonglin__logger(config, LOG_ERR, "unable to write pidfile: %s", strerror(errno));
        close(pid_fd);
        return ERR_PID;
    }
    else if ((size_t)ret != len)
    {
        wangyonglin__logger(config, LOG_ERR, "unable to write pidfile: wrote"
                                     " %" PRIdMAX " of %" PRIuMAX " bytes.",
                    (intmax_t)ret, (uintmax_t)len);
        close(pid_fd);
        return ERR_PID;
    }
    close(pid_fd);

    return ERR_SUCCESS;
}
/**
 * \brief Remove the pid file (used at the startup)
 *
 * \param config to the name of the pid file to write (optarg)
 */
void wangyonglin__pid_remove(struct wangyonglin__config *config)
{
    if (config->pid_file != NULL)
    {
        /* we ignore the result, the user may have removed the file already. */
        (void)unlink(config->pid_file);
    }
}

/**
 * \brief Check a pid file (used at the startup)
 *        This commonly needed by the init scripts
 *
 * \param config to the name of the pid file to write (optarg)
 *
 * \retval ERR_SUCCESS if succes
 * \retval ERR_PID on failure
 */
int wangyonglin__pid_test(struct wangyonglin__config *config)
{
    if (access(config->pid_file, F_OK) == 0)
    {
        /* Check if the existing process is still alive. */
        pid_t pidv;
        FILE *pf;

        pf = fopen(config->pid_file, "r");
        if (pf == NULL)
        {
            wangyonglin__logger(config, LOG_ERR, "pid file '%s' exists and can not be read. Aborting!",
                        config->pid_file);
            return ERR_PID;
        }

        if (fscanf(pf, "%d", &pidv) == 1 && kill(pidv, 0) == 0)
        {
            fclose(pf);
            wangyonglin__logger(config, LOG_ERR, "pid file '%s' exists. Is program already running? Aborting!",
                        config->pid_file);
            return ERR_PID;
        }

        fclose(pf);
    }
    return ERR_SUCCESS;
}