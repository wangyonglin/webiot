#ifndef _WANGYONGLIN_HTTPS_SSL_INCLUDE_
#define _WANGYONGLIN_HTTPS_SSL_INCLUDE_
#include <wangyonglin/linux.h>
#include <wangyonglin/wangyonglin.h>


void wangyonglin_openssl_init();
void wangyonglin_openssl_cleanup();
SSL_CTX *wangyonglin_openssl_context_create(struct wangyonglin__config *config);
void wangyonglin_openssl_context_configure(struct wangyonglin__config *config,SSL_CTX *ctx, const char *certificate_chain, const char *key);

#endif