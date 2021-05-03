#ifndef INCLUDE_PUBLIC_HMACSHA1_H
#define INCLUDE_PUBLIC_HMACSHA1_H
#include <wangyonglin/linux.h>
#include <wangyonglin/wangyonglin.h>
size_t openssl__hmacsha1_encode(struct wangyonglin__config * config,const void *key, unsigned char *data, unsigned char *dest);
#endif