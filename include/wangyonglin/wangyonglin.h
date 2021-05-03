#ifndef INCLUDE_WANGYONGLIN_WANGYONGLIN_H
#define INCLUDE_WANGYONGLIN_WANGYONGLIN_H
#include <wangyonglin/buffer.h>
#include <wangyonglin/conf.h>
#include <wangyonglin/config.h>
#include <wangyonglin/signal.h>
#include <wangyonglin/memory.h>
#include <wangyonglin/core.h>
#include <wangyonglin/logging.h>
#include <wangyonglin/string.h>
#include <wangyonglin/error.h>
#include <wangyonglin/pid.h>
#include <wangyonglin/daemon.h>
#include <wangyonglin/time.h>
/* Log types */
#define LOG_NONE 0
#define LOG_INFO (1 << 0)
#define LOG_NOTICE (1 << 1)
#define LOG_WARNING (1 << 2)
#define LOG_ERR (1 << 3)
#define LOG_DEBUG (1 << 4)
#define LOG_SUBSCRIBE (1 << 5)
#define LOG_UNSUBSCRIBE (1 << 6)
#define LOG_WEBSOCKETS (1 << 7)
#define LOG_INTERNAL 0x80000000U
#define LOG_ALL 0xFFFFFFFFU

/* Error values */
enum err_t
{
	ERR_AUTH_CONTINUE = -4,
	ERR_NO_SUBSCRIBERS = -3,
	ERR_SUB_EXISTS = -2,
	ERR_CONN_PENDING = -1,
	ERR_SUCCESS = 0,
	ERR_NOMEM = 1,
	ERR_PROTOCOL = 2,
	ERR_INVAL = 3,
	ERR_NO_CONN = 4,
	ERR_CONN_REFUSED = 5,
	ERR_NOT_FOUND = 6,
	ERR_CONN_LOST = 7,
	ERR_TLS = 8,
	ERR_PAYLOAD_SIZE = 9,
	ERR_NOT_SUPPORTED = 10,
	ERR_AUTH = 11,
	ERR_ACL_DENIED = 12,
	ERR_UNKNOWN = 13,
	ERR_ERRNO = 14,
	ERR_EAI = 15,
	ERR_PROXY = 16,
	ERR_PLUGIN_DEFER = 17,
	ERR_MALFORMED_UTF8 = 18,
	ERR_KEEPALIVE = 19,
	ERR_LOOKUP = 20,
	ERR_MALFORMED_PACKET = 21,
	ERR_DUPLICATE_PROPERTY = 22,
	ERR_TLS_HANDSHAKE = 23,
	ERR_QOS_NOT_SUPPORTED = 24,
	ERR_OVERSIZE_PACKET = 25,
	ERR_OCSP = 26,
	ERR_TIMEOUT = 27,
	ERR_RETAIN_NOT_SUPPORTED = 28,
	ERR_TOPIC_ALIAS_INVALID = 29,
	ERR_ADMINISTRATIVE_ACTION = 30,
	ERR_ALREADY_EXISTS = 31,
	ERR_DAEMON = 32,
	ERR_PID = 33,
};

#endif
