#ifndef INCLUDE_WANGYONGLIN_LOGGING_H
#define INCLUDE_WANGYONGLIN_LOGGING_H
#include <wangyonglin/linux.h>
#include <wangyonglin/wangyonglin.h>

/* ============================================================
 * Logging functions
 * ============================================================ */
int logify_init(configify_t *config);
int logify_close(configify_t *config);
int logify_printf(configify_t *config, unsigned int priority, const char *fmt, ...) __attribute__((format(printf, 3, 4)));
int logify_vprintf(configify_t *config, unsigned int priority, const char *fmt, va_list va);

#if 1

#endif

#endif