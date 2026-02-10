#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>

void mm_init(void);
void *mm_malloc_impl(size_t size, const char *file, int line);
void *mm_calloc_impl(size_t count, size_t size, const char *file, int line);
char *mm_strdup_impl(const char *s, const char *file, int line);
void mm_free_impl(void *ptr, const char *file, int line);
void mm_report(void);
void mm_cleanup(void);

#define mm_malloc(sz) mm_malloc_impl((sz), __FILE__, __LINE__)
#define mm_calloc(n, sz) mm_calloc_impl((n), (sz), __FILE__, __LINE__)
#define mm_strdup(s) mm_strdup_impl((s), __FILE__, __LINE__)
#define mm_free(p) mm_free_impl((p), __FILE__, __LINE__)

#endif
