#ifndef INCLUDE_WANGYONGLIN_WANGYONGLIN_H
#define INCLUDE_WANGYONGLIN_WANGYONGLIN_H
#include <wangyonglin/memory.h>
#include <wangyonglin/conf.h>
#include <wangyonglin/signal.h>
#include <wangyonglin/config.h>
#include <wangyonglin/message.h>
#include <wangyonglin/logging.h>
#include <wangyonglin/string.h>
#include <wangyonglin/error.h>
#include <wangyonglin/pid.h>
#include <wangyonglin/daemon.h>
#include <wangyonglin/time.h>
#include <wangyonglin/uuid.h>
#include <wangyonglin/socket.h>
#include <application/application.h>
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
	ERR_SIGNAL	= -3,
	ERR_UNKNOWN	= -2,
	ERR_DEBUG	= -1,
	ERR_SUCCESS = 0,
	ERR_CONFIG	= 1,
	ERR_LOGGING = 2,
	ERR_PID		= 3,
	ERR_ERRNO	= 4,
	ERR_DAEMON	= 5,
	ERR_TIMEOUT = 100,
};


#endif
