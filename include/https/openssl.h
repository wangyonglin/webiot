#ifndef _WANGYONGLIN_HTTPS_SSL_INCLUDE_
#define _WANGYONGLIN_HTTPS_SSL_INCLUDE_
#include <wangyonglin/linux.h>
#include <wangyonglin/wangyonglin.h>

void https__openssl_init();
void https__openssl_cleanup();
SSL_CTX *https__openssl_create(configify_t *config);
void https__openssl_set(configify_t *config, SSL_CTX *ctx, const char *certificate_chain, const char *key);

#endif