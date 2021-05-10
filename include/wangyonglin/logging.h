#ifndef INCLUDE_WANGYONGLIN_LOGGING_H
#define INCLUDE_WANGYONGLIN_LOGGING_H
#include <wangyonglin/linux.h>
#include <wangyonglin/wangyonglin.h>

/* ============================================================
 * Logging functions
 * ============================================================ */
int wangyonglin__log_init(struct wangyonglin__config *config);
int wangyonglin__log_close(struct wangyonglin__config *config);
int wangyonglin__log_printf(struct wangyonglin__config *config, unsigned int priority, const char *fmt, ...) __attribute__((format(printf, 3, 4)));
int wangyonglin__log_vprintf(struct wangyonglin__config *config, unsigned int priority, const char *fmt, va_list va);

#if 1
#define log__printf wangyonglin__log_printf
#define wangyonglin__logger wangyonglin__log_printf
#endif

#endif