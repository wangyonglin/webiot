#include <wangyonglin/config.h>
#include <wangyonglin/core.h>


SSL_CTX *wangyonglin_openssl_context_create()
{
    const SSL_METHOD *method;
    SSL_CTX *ctx;
    method = SSLv23_server_method();
    ctx = SSL_CTX_new(method);
    if (!ctx)
    {
        perror("Unable to create SSL context");
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }
    SSL_CTX_set_options(ctx, SSL_OP_SINGLE_DH_USE | SSL_OP_SINGLE_ECDH_USE | SSL_OP_NO_SSLv2);
    EC_KEY *ecdh = EC_KEY_new_by_curve_name(NID_X9_62_prime256v1);
    if (!ecdh)
        printf("EC_KEY_new_by_curve_name");
    if (1 != SSL_CTX_set_tmp_ecdh(ctx, ecdh))
        printf("SSL_CTX_set_tmp_ecdh");
    return ctx;
}

void wangyonglin_openssl_context_configure(SSL_CTX *ctx, const char *certificate_chain, const char *private_key)
{
    SSL_CTX_set_ecdh_auto(ctx, 1);
    /* Set the key and cert */
    if (SSL_CTX_use_certificate_file(ctx, certificate_chain, SSL_FILETYPE_PEM) <= 0)
    {
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }

    if (SSL_CTX_use_PrivateKey_file(ctx, private_key, SSL_FILETYPE_PEM) <= 0)
    {
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }
    if (SSL_CTX_check_private_key(ctx) <= 0)
    {
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }
}

void wangyonglin_openssl_init()
{
    SSL_library_init();
    SSL_load_error_strings();
    OpenSSL_add_all_algorithms();
}
void wangyonglin_openssl_cleanup()
{
    EVP_cleanup();
}