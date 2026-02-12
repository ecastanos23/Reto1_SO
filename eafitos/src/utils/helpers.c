#include <ctype.h>
#include <string.h>

#include "utils.h"

// Utilidades de texto para operaciones con mayusculas/minusculas.
char *helpers_strdup_lower(const char *s) {
	if (s == NULL) {
		return NULL;
	}

	size_t len = strlen(s) + 1;
	char *out = mm_malloc(len);
	for (size_t i = 0; i < len; i++) {
		unsigned char c = (unsigned char)s[i];
		out[i] = (char)tolower(c);
	}
	return out;
}

// Busca una subcadena sin distinguir mayusculas/minusculas.
int helpers_contains_case_insensitive(const char *haystack, const char *needle) {
	if (haystack == NULL || needle == NULL || needle[0] == '\0') {
		return 0;
	}

	char *hay = helpers_strdup_lower(haystack);
	char *need = helpers_strdup_lower(needle);
	int result = 0;

	if (hay != NULL && need != NULL) {
		result = (strstr(hay, need) != NULL) ? 1 : 0;
	}

	mm_free(hay);
	mm_free(need);
	return result;
}
