#ifndef INCLUDE_WANGYONGLIN_BUFFER_H
#define INCLUDE_WANGYONGLIN_BUFFER_H
#include <wangyonglin/linux.h>
#include <wangyonglin/wangyonglin.h>
typedef struct wangyonglin__buffer wangyonglin__buffer_t;
struct wangyonglin__buffer
{
    uint8_t *val;
};
void buffer(struct wangyonglin__buffer *buffer, size_t len);
void buffer__null(struct wangyonglin__buffer *buffer);
void buffer__cleanup(struct wangyonglin__buffer *buffer);
#endif