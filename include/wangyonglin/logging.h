#ifndef _WANGYONGLIN_LOGGING_H_INCLUDE_
#define _WANGYONGLIN_LOGGING_H_INCLUDE_
#include <wangyonglin/linux_config.h>
#include <wangyonglin/wangyonglin.h>

/* ============================================================
 * Logging functions
 * ============================================================ */
int log__init(struct wangyonglin__config *config);
int log__close(struct wangyonglin__config *config);
int log__printf(struct wangyonglin__config *config, unsigned int priority, const char *fmt, ...) __attribute__((format(printf, 3, 4)));
int log__vprintf(struct wangyonglin__config *config, unsigned int priority, const char *fmt, va_list va);
#endif