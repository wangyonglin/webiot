
#ifndef INCLUDE_WANGYONGLIN_SIGNAL_H
#define INCLUDE_WANGYONGLIN_SIGNAL_H
#include <wangyonglin/linux.h>
#include <wangyonglin/wangyonglin.h>
struct wangyonglin__signal
{
    struct sigaction act;
    union sigval sval;
};

#endif