#include <wangyonglin/linux.h>
#include <wangyonglin/wangyonglin.h>
#include <public/base64.h>
#define KEY_LENGTH 24
#define SEPARATOR "$"
#define SALTLEN 12

int password_new(struct wangyonglin__config *config, const char *password, uint8_t *data)
{
    int iterations = 901, rc, blen;
    unsigned char saltbytes[SALTLEN];
    char *salt, *b64;
    unsigned char key[128];
    rc = RAND_bytes(saltbytes, SALTLEN);
    if (rc == 0)
    {
        wangyonglin__logger(config, LOG_DEBUG, "Cannot get random bytes for salt!");
        return ERR_DEBUG;
    }

    base64_encode(saltbytes, SALTLEN, &salt);

#ifdef RAW_SALT
    PKCS5_PBKDF2_HMAC(password, strlen(password),
                      (unsigned char *)saltbytes, SALTLEN,
                      iterations,
                      EVP_sha256(), KEY_LENGTH, key);
#else
    int saltlen;
    saltlen = strlen(salt);

    PKCS5_PBKDF2_HMAC(password, strlen(password),
                      (unsigned char *)salt, saltlen,
                      iterations,
                      EVP_sha256(), KEY_LENGTH, key);
#endif

    blen = base64_encode(key, KEY_LENGTH, &b64);
    if (blen > 0)
    {
        rc= sprintf(data,"PBKDF2$%s$%d$%s$%s","sha256",iterations, salt, b64);
        free(b64);
    }

    return rc;
}