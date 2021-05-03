#include <wangyonglin/linux.h>
#include <wangyonglin/wangyonglin.h>

/** 
 申请句柄为buffer
 @param buffer 句柄
 @param len 申请内存大小
 */
void buffer(struct wangyonglin__buffer *buffer, size_t len)
{
    buffer->val = (uint8_t *)malloc(sizeof(char) * len);
    memset(buffer->val, 0, sizeof(buffer->val));
}
/**
 清空句柄内的val值
 @param buffer 句柄
 */
void buffer__null(struct wangyonglin__buffer *buffer)
{
    if (buffer->val)
    {
        memset(buffer->val, 0, strlen(buffer->val));
    }
}
/**
 清空句柄内的val值
 @param buffer 句柄
 */
void buffer__cleanup(struct wangyonglin__buffer *buffer)
{
    if (buffer->val != NULL)
    {
        free(buffer->val);
        buffer->val = NULL;
    }
}