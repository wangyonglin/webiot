#ifndef _WANGYONGLIN_CORE_H_INCLUDE_
#define _WANGYONGLIN_CORE_H_INCLUDE_


typedef u_int wangyonglin_uint_t;


typedef struct wangyonglin_pid_s wangyonglin_pid_t;
typedef struct wangyonglin_conf_s wangyonglin_conf_t;
typedef struct wangyonglin_log_s wangyonglin_log_t;
typedef struct wangyonglin_time_s wangyonglin_time_t;


#define  WANGYONGLIN_OK          0
#define  WANGYONGLIN_ERROR      -1
#define  WANGYONGLIN_AGAIN      -2
#define  WANGYONGLIN_BUSY       -3
#define  WANGYONGLIN_DONE       -4
#define  WANGYONGLIN_DECLINED   -5
#define  WANGYONGLIN_ABORT      -6

#include <wangyonglin/pid.h>
#include <wangyonglin/conf.h>

#include <wangyonglin/time.h>
#include <wangyonglin/string.h>
#include <wangyonglin/file.h>
#include <wangyonglin/log.h>
#include <wangyonglin/json.h>




#endif /**_WANGYONGLIN_CORE_H_INCLUDE_**/
