#include <wangyonglin/linux.h>
#include <wangyonglin/wangyonglin.h>

size_t public__hmacsha1_encode(struct wangyonglin__config * config,const void *key, unsigned char *data, unsigned char *dest){
     if (data == NULL || dest == NULL)
        return -1;
    unsigned char *result;
    unsigned int len = 50;
    result = (unsigned char *)malloc(sizeof(char) * len);
    HMAC_CTX *ctx = HMAC_CTX_new();
    HMAC_CTX_reset(ctx);
    // Using sha1 hash engine here.
    // You may use other hash engines. e.g EVP_md5(), EVP_sha224, EVP_sha512, etc,EVP_sha1
    HMAC_Init_ex(ctx, key, strlen(key), EVP_sha1(), NULL);
    HMAC_Update(ctx, data, strlen(data));
    HMAC_Final(ctx, result, &len);
    HMAC_CTX_free(ctx);

    BIO *b64, *bio;
    BUF_MEM *bptr = NULL;
    size_t size = 0;

    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);
    BIO_write(bio, result, len);
    BIO_flush(bio);
    BIO_get_mem_ptr(bio, &bptr);
    memcpy(dest, bptr->data, bptr->length);
    dest[bptr->length] = '\0';
    size = bptr->length;
    BIO_free_all(bio);
    return size;
}