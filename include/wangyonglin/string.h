#ifndef INCLUDE_WANGYONGLIN_STRING_H
#define INCLUDE_WANGYONGLIN_STRING_H
#include <wangyonglin/linux.h>
#include <wangyonglin/wangyonglin.h>
typedef struct string_s string_t;
#define int_t int;
struct string_s{
    size_t len;
    uint8_t *data;
};
#define string(str)     { sizeof(str) - 1, (u_char *) str }

#define string_setting(str, text) \
    (str)->len = strlen(text);                \
    (str)->data = (char *)text
#define string_null(str) \
    (str)->len = 0;                  \
    (str)->data = NULL
#define null_string \
    {                           \
        0, NULL                 \
    }



typedef struct wangyonglin_string_s wangyonglin_string_t;
struct wangyonglin_string_s
{
    size_t len;
    uint8_t *data;
};
#define wangyonglin_string_setting(str, text) \
    (str)->len = strlen(text);                \
    (str)->data = (char *)text
#define wangyonglin_string_null(str) \
    (str)->len = 0;                  \
    (str)->data = NULL
#define wangyonglin_null_string \
    {                           \
        0, NULL                 \
    }




#endif