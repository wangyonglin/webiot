#ifndef _WANGYONGLIN_HMACSHA1_H_INCLUDE_
#define _WANGYONGLIN_HMACSHA1_H_INCLUDE_

#include <wangyonglin/linux_config.h>
#include <wangyonglin/wangyonglin.h>
#include <openssl/evp.h>
#include <openssl/hmac.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>
size_t wangyonglin_hmacsha1_encode(const void *key, unsigned char *data, unsigned char *dest);
#endif