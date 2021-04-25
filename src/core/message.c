#include <wangyonglin/linux_config.h>
#include <wangyonglin/wangyonglin.h>

wangyonglin_message_id_t wangyonglin_message_create()
{

    wangyonglin_message_id_t msgid = msgget(IPC_PRIVATE, 0600);
    if (msgid < 0)
    {
        perror("msgget");
        return 1;
    }

    printf("%d\n", msgid);
    return msgid;
}

void wangyonglin_message_msgsnd(wangyonglin_message_id_t id, int type, unsigned char *data, size_t len)
{
    wangyonglin_message_t msg;
    msg.type = type;
    strncpy(msg.msg, data, len);
    if (msgsnd(id, &msg, MTEXTSIZE, 0) != 0)
    {
        perror("msgsnd");
    }
}

ssize_t wangyonglin_message_msgrcv(wangyonglin_message_id_t id, int type, wangyonglin_message_t * msg)
{
    ssize_t rc = 0;
    rc = msgrcv(id, msg, MTEXTSIZE, type, 0);
    if (rc<= 0)
    {
        perror("msgrcv");
        return rc;
    }
    return rc;
}

void wangyonglin_message_msgctl(wangyonglin_message_id_t id)
{
    struct msqid_ds mds;
    if (msgctl(id, IPC_RMID, &mds) != 0)
    {
        perror("msgctl");
    }
}