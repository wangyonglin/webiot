#include <wangyonglin/linux.h>
#include <wangyonglin/wangyonglin.h>

size_t wangyonglin__executable(struct wangyonglin__config *config)
{

   /*

    struct dirent *direntp;
    config->dir = opendir(config->exe_dirname);

    while ((direntp = readdir(config->dir)) != NULL)
    {
        printf("\t ### %s %d \r\n", direntp->d_name, direntp->d_type);
        //  if (1)break;
        if (strcmp(direntp->d_name, "..") || direntp->d_type == 4)
        {
            config->dir = opendir(direntp->d_name);
            while ((direntp = readdir(config->dir)) != NULL)
            {
                printf("\t @@@c%s %d \r\n", direntp->d_name, direntp->d_type);
            }
        }
    }

    closedir(config->dir);
*/
    return 1;
}