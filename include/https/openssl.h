#ifndef _WANGYONGLIN_HTTPS_SSL_INCLUDE_
#define _WANGYONGLIN_HTTPS_SSL_INCLUDE_
#include <wangyonglin/config.h>
#include <wangyonglin/core.h>


void wangyonglin_openssl_init();
void wangyonglin_openssl_cleanup();
SSL_CTX *wangyonglin_openssl_context_create();
void wangyonglin_openssl_context_configure(SSL_CTX *ctx, const char *certificate_chain, const char *key);

#endif