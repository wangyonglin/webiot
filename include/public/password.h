#ifndef PUBLIC_PASSWORD_H
#define PUBLIC_PASSWORD_H
#include <wangyonglin/linux.h>
#include <wangyonglin/wangyonglin.h>
int password_new(struct wangyonglin__config *config, const char *password, uint8_t *data);
#endif