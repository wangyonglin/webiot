#ifndef INCLUDE_WANGYONGLIN_LINUX_H
#define INCLUDE_WANGYONGLIN_LINUX_H
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stddef.h>
#include <assert.h>
#include <stdlib.h> /* malloc, free */
#include <stdio.h>  /* fopen, fread, fclose */
#include <string.h> /* strcmp, strdup */
#include <ctype.h>  /* isspace */
#include <errno.h>  /* ENOMEM, EINVAL, ENOENT */
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <stdint.h>
#include <poll.h>
#include <sys/epoll.h>
#include <sys/time.h>
#include <pthread.h>
#include <err.h>
#include <dirent.h>
//到消息队列 ipc msg
#include <sys/ipc.h>
#include <sys/msg.h>
#include <ctype.h>
//OPENSSL　证书
#include <openssl/err.h>
#include <openssl/ssl.h>
#include <openssl/bn.h>
// TOML 配置文件
#include <stdbool.h>
#endif
