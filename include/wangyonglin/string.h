#ifndef _WANGYONGLIN_STRING_H_INCLUDE_
#define _WANGYONGLIN_STRING_H_INCLUDE_

#include <wangyonglin/config.h>
#include <wangyonglin/core.h>

#define  wangyonglin_buffer_t	char

typedef char *	wangyonglin_str_t;
typedef int 	wangyonglin_int_t;

typedef struct {
	size_t      len;
	u_char     *data;
} wangyonglin_string_t;
	

#define wangyonglin_string(str)     { sizeof(str) - 1, (u_char *) str }
#define wangyonglin_null_string     { 0, NULL }
#define wangyonglin_str_set(str, text)                                               \
	    (str)->len = sizeof(text) - 1; (str)->data = (u_char *) text
#define wangyonglin_string_null(str)   (str)->len = 0; (str)->data = NULL


#endif /**_WANGYONGLIN_STRING_H_INCLUDE_**/
