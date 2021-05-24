#ifndef INCLUDE_WANGYONGLIN_BUFFER_H
#define INCLUDE_WANGYONGLIN_BUFFER_H
#include <wangyonglin/linux.h>
#include <wangyonglin/wangyonglin.h>
typedef struct wangyonglin__buffer wangyonglin__buffer_t;
struct wangyonglin__buffer
{
    size_t length; /* current number of bytes */
    uint8_t *data;
};
void wangyonglin__buffer_register(struct wangyonglin__buffer *buffer, size_t length);
void wangyonglin__buffer_setting(struct wangyonglin__buffer *buffer, const char *string, size_t length);
int wangyonglin__buffer_format(struct wangyonglin__buffer *buffer, const char *fmt, ...);
void wangyonglin__buffer_null(struct wangyonglin__buffer *buffer);
void wangyonglin__buffer_cleanup(struct wangyonglin__buffer *buffer);
#endif