#include <wangyonglin/linux.h>
#include <wangyonglin/wangyonglin.h>

/** 
 申请句柄为buffer
 @param buffer 句柄
 @param len 申请内存大小
 @retval void
 */
void wangyonglin__buffer_register(struct wangyonglin__buffer *buffer, size_t length)
{
    buffer->data = (uint8_t *)malloc(sizeof(uint8_t) * length);
    memset(buffer->data, 0, sizeof(buffer->data));
    buffer->length = 0;
}

void wangyonglin__buffer_setting(struct wangyonglin__buffer *buffer, const char *string, size_t length)
{
    strncpy(buffer->data, string, length);
    buffer->length = strlen(buffer->data);
}
/**
 清空句柄内的val值
 @param buffer 句柄
 */
void wangyonglin__buffer_null(struct wangyonglin__buffer *buffer)
{
    if (buffer->data)
    {
        memset(buffer->data, 0, sizeof(buffer->data));
        buffer->length = 0;
    }
}
/**
 清空句柄内的val值
 @param buffer 句柄
 */
void wangyonglin__buffer_cleanup(struct wangyonglin__buffer *buffer)
{
    if (buffer->data != NULL)
    {
        free(buffer->data);
        buffer->data = NULL;
    }
    if (buffer != NULL)
    {
        free(buffer);
        buffer = NULL;
    }
}

int wangyonglin__buffer_format(struct wangyonglin__buffer *buffer, const char *fmt, ...)
{
    va_list va;
    int rc;
    va_start(va, fmt);
    rc = vsprintf(buffer->data, fmt, va);
    buffer->length = rc;
    va_end(va);
    return rc;
}