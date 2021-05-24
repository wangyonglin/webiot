#ifndef INCLUDE_WANGYONGLIN_BASE64_H
#define INCLUDE_WANGYONGLIN_BASE64_H
#include <wangyonglin/linux.h>
#include <wangyonglin/wangyonglin.h>

int wangyonglin__base64__encode(unsigned char *in, unsigned int in_len, char **encoded);
int wangyonglin__base64__decode(char *in, unsigned char **decoded, unsigned int *decoded_len);
#endif