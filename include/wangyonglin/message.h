#ifndef _WANGYONGLIN_MESSAGE_H_INCLUDE_
#define _WANGYONGLIN_MESSAGE_H_INCLUDE_
#include <wangyonglin/config.h>
#include <wangyonglin/core.h>
#define MTEXTSIZE 1024
typedef struct wangyonglin_message_s wangyonglin_message_t;
#define wangyonglin_message_id_t int
struct wangyonglin_message_s
{
    int type;
    unsigned char msg[MTEXTSIZE];
};

wangyonglin_message_id_t wangyonglin_message_create();
void wangyonglin_message_msgsnd(wangyonglin_message_id_t id, int type, unsigned char *data, size_t len);
ssize_t wangyonglin_message_msgrcv(wangyonglin_message_id_t id, int type, wangyonglin_message_t * msg);

void wangyonglin_message_msgctl(wangyonglin_message_id_t id);

#endif;