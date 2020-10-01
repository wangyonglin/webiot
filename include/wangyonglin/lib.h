#ifndef _WANGYONGLIN_LIB_H_INCLUDE_
#define _WANGYONGLIN_LIB_H_INCLUDE_
#include <wangyonglin/config.h>
#include <wangyonglin/core.h>
#define wangyonglin_error_exit(m)         \
    do                      \
    {                       \
        perror(m);          \
        exit(EXIT_FAILURE); \
    } while (0)
typedef enum wangyonglin_result_e wangyonglin_result_t;
typedef enum rcwangyonglin_rc_e wangyonglin_rc_t;
enum wangyonglin_result_e
{
    wangyonglin_result_error = -2,
    wangyonglin_result_failure = -1,
    wangyonglin_result_success
};

enum rcwangyonglin_rc_e
{

    declined = -5,
    done = -4,
    busy = -3,
    again = -2,
    error = -1,
    ok = 0
};




#endif /**_WANGYONGLIN_LIB_H_INCLUDE_**/