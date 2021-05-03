#include <wangyonglin/linux.h>
#include <wangyonglin/wangyonglin.h>

void wangyonglin_error_exit(int __status, const char *__format, ...)
{
    do
    {
        va_list args;
        va_start(args, __format);
        perror((const char *)args);
        exit(__status);
    } while (0);
}
void wangyonglin_error_perror(const char *__format, ...)
{
    va_list args;
    va_start(args, __format);
    perror((const char *)args);
}