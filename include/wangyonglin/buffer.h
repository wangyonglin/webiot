#ifndef INCLUDE_WANGYONGLIN_BUFFER_H
#define INCLUDE_WANGYONGLIN_BUFFER_H
#include <wangyonglin/linux.h>
#include <wangyonglin/wangyonglin.h>
typedef struct wangyonglin__buffer wangyonglin__buffer_t;
struct wangyonglin__buffer
{
    size_t length; /* current number of bytes */
    uint8_t *data;
    size_t max; /* size of buffer */
    unsigned long flags;
};
void wangyonglin__buffer(struct wangyonglin__buffer *buffer, size_t length);
void wangyonglin__buffer_set(struct wangyonglin__buffer *buffer, const char *string,size_t length);
void wangyonglin__buffer_null(struct wangyonglin__buffer *buffer);
void wangyonglin__buffer_cleanup(struct wangyonglin__buffer *buffer);
#endif