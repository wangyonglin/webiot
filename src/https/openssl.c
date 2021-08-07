#include <wangyonglin/linux.h>
#include <wangyonglin/wangyonglin.h>

SSL_CTX *https__openssl_create(configify_t *config)
{
    const SSL_METHOD *method;
    SSL_CTX *ctx;
    method = SSLv23_server_method();
    ctx = SSL_CTX_new(method);
    if (!ctx)
    {
        logify_printf(config, LOG_ERR, "Unable to create SSL context");
        //ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }
    SSL_CTX_set_options(ctx, SSL_OP_SINGLE_DH_USE | SSL_OP_SINGLE_ECDH_USE | SSL_OP_NO_SSLv2);
    EC_KEY *ecdh = EC_KEY_new_by_curve_name(NID_X9_62_prime256v1);
    if (!ecdh)
        logify_printf(config, LOG_ERR, "EC_KEY_new_by_curve_name");
    if (1 != SSL_CTX_set_tmp_ecdh(ctx, ecdh))
        logify_printf(config, LOG_ERR, "SSL_CTX_set_tmp_ecdh");
    return ctx;
}

void https__openssl_set(configify_t *config, SSL_CTX *ctx, const char *certificate_chain, const char *private_key)
{
    SSL_CTX_set_ecdh_auto(ctx, 1);
    /* Set the key and cert */
    if (SSL_CTX_use_certificate_file(ctx, certificate_chain, SSL_FILETYPE_PEM) <= 0)
    {
        // ERR_print_errors_fp(stderr);
        logify_printf(config, LOG_ERR, "Set the  cert %s", certificate_chain);
        exit(EXIT_FAILURE);
    }

    if (SSL_CTX_use_PrivateKey_file(ctx, private_key, SSL_FILETYPE_PEM) <= 0)
    {
        //ERR_print_errors_fp(stderr);
        logify_printf(config, LOG_ERR, "Set the  key %s", private_key);
        exit(EXIT_FAILURE);
    }
    if (SSL_CTX_check_private_key(ctx) <= 0)
    {
        logify_printf(config, LOG_ERR, "Check the  private key");
        //ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }
}

void https__openssl_init()
{
    SSL_library_init();
    SSL_load_error_strings();
    OpenSSL_add_all_algorithms();
}
void https__openssl_cleanup()
{
    EVP_cleanup();
}