#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>

// API de utilidades: memoria con seguimiento, manejo de errores y helpers.
void mm_init(void);
void *mm_malloc_impl(size_t size, const char *file, int line);
void *mm_calloc_impl(size_t count, size_t size, const char *file, int line);
char *mm_strdup_impl(const char *s, const char *file, int line);
void mm_free_impl(void *ptr, const char *file, int line);
void mm_report(void);
void mm_cleanup(void);

// API de reporte de errores (stderr + log opcional).
void err_message(const char *context, const char *message);
void err_errno(const char *context);
void err_exit_errno(const char *context, int code);
int err_set_log_file(const char *path);
void err_close_log(void);

// Helpers de texto para busquedas sin sensibilidad a mayusculas.
char *helpers_strdup_lower(const char *s);
int helpers_contains_case_insensitive(const char *haystack, const char *needle);

// Macros para capturar archivo/linea al usar el administrador de memoria.
#define mm_malloc(sz) mm_malloc_impl((sz), __FILE__, __LINE__)
#define mm_calloc(n, sz) mm_calloc_impl((n), (sz), __FILE__, __LINE__)
#define mm_strdup(s) mm_strdup_impl((s), __FILE__, __LINE__)
#define mm_free(p) mm_free_impl((p), __FILE__, __LINE__)

#endif
