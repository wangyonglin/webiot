#include <wangyonglin/linux.h>
#include <wangyonglin/wangyonglin.h>

/** 
 申请句柄为buffer
 @param buffer 句柄
 @param len 申请内存大小
 */
void buffer(struct wangyonglin__buffer *buffer, size_t length)
{
    buffer->data = (uint8_t *)malloc(sizeof(char) * length);
    memset(buffer->data, 0, sizeof(buffer->data));
    buffer->length = 0;
    buffer->max = length;
}

void buffer__set(struct wangyonglin__buffer *buffer, const char *string,size_t length)
{
    strncpy(buffer->data,string,length);
    buffer->length = strlen(buffer->data);
}
/**
 清空句柄内的val值
 @param buffer 句柄
 */
void buffer__null(struct wangyonglin__buffer *buffer)
{
    if (buffer->data)
    {
        memset(buffer->data, 0, sizeof(buffer->data));
        buffer->length=0;
    }
}
/**
 清空句柄内的val值
 @param buffer 句柄
 */
void buffer__cleanup(struct wangyonglin__buffer *buffer)
{
    if (buffer->data != NULL)
    {
        free(buffer->data);
        buffer->data = NULL;
    }
    if (buffer!=NULL)
    {
        //free(buffer);
        buffer = NULL;
    }
}