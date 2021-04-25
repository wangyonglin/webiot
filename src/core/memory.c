#include <wangyonglin/linux_config.h>
#include <wangyonglin/wangyonglin.h>

void *wangyonglin__calloc(size_t nmemb, size_t size)
{
}
void wangyonglin__free(void *mem)
{
    if (mem)
    {
        free(mem);
    }
}
void *wangyonglin__malloc(size_t size)
{
    void *mem;
    mem = malloc(size);
    return mem;
}
