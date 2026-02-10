#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

typedef struct MemoryNode {
	void *ptr;
	size_t size;
	const char *file;
	int line;
	struct MemoryNode *next;
} MemoryNode;

static MemoryNode *mm_head = NULL;

void mm_init(void) {
	mm_head = NULL;
}

static MemoryNode *mm_new_node(void *ptr, size_t size, const char *file, int line) {
	MemoryNode *node = (MemoryNode *)malloc(sizeof(MemoryNode));
	if (node == NULL) {
		fprintf(stderr, "mm: fallo al asignar nodo de control en %s:%d\n", file, line);
		free(ptr);
		exit(EXIT_FAILURE);
	}
	node->ptr = ptr;
	node->size = size;
	node->file = file;
	node->line = line;
	node->next = mm_head;
	mm_head = node;
	return node;
}

void *mm_malloc_impl(size_t size, const char *file, int line) {
	if (size == 0) {
		size = 1;
	}
	void *ptr = malloc(size);
	if (ptr == NULL) {
		fprintf(stderr, "mm: fallo malloc(%zu) en %s:%d\n", size, file, line);
		exit(EXIT_FAILURE);
	}
	mm_new_node(ptr, size, file, line);
	return ptr;
}

void *mm_calloc_impl(size_t count, size_t size, const char *file, int line) {
	if (count == 0 || size == 0) {
		count = 1;
		size = 1;
	}
	void *ptr = calloc(count, size);
	if (ptr == NULL) {
		fprintf(stderr, "mm: fallo calloc(%zu, %zu) en %s:%d\n", count, size, file, line);
		exit(EXIT_FAILURE);
	}
	mm_new_node(ptr, count * size, file, line);
	return ptr;
}

char *mm_strdup_impl(const char *s, const char *file, int line) {
	if (s == NULL) {
		fprintf(stderr, "mm: strdup con NULL en %s:%d\n", file, line);
		exit(EXIT_FAILURE);
	}
	size_t len = strlen(s) + 1;
	char *ptr = (char *)mm_malloc_impl(len, file, line);
	memcpy(ptr, s, len);
	return ptr;
}

void mm_free_impl(void *ptr, const char *file, int line) {
	if (ptr == NULL) {
		return;
	}

	MemoryNode *prev = NULL;
	MemoryNode *cur = mm_head;
	while (cur != NULL && cur->ptr != ptr) {
		prev = cur;
		cur = cur->next;
	}

	if (cur == NULL) {
		fprintf(stderr, "mm: puntero no registrado liberado en %s:%d\n", file, line);
		free(ptr);
		return;
	}

	if (prev == NULL) {
		mm_head = cur->next;
	} else {
		prev->next = cur->next;
	}

	free(cur->ptr);
	free(cur);
}

void mm_report(void) {
	size_t total = 0;
	int count = 0;
	MemoryNode *cur = mm_head;

	if (cur == NULL) {
		return;
	}

	fprintf(stderr, "\nmm: posibles fugas de memoria:\n");
	while (cur != NULL) {
		fprintf(stderr, "  - %p (%zu bytes) asignado en %s:%d\n",
			cur->ptr, cur->size, cur->file, cur->line);
		total += cur->size;
		count++;
		cur = cur->next;
	}
	fprintf(stderr, "mm: total %d asignaciones, %zu bytes\n", count, total);
}

void mm_cleanup(void) {
	MemoryNode *cur = mm_head;
	while (cur != NULL) {
		MemoryNode *next = cur->next;
		free(cur->ptr);
		free(cur);
		cur = next;
	}
	mm_head = NULL;
}
