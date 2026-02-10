#include <stdio.h>
#include <string.h>

#include "utils.h"

int main(void) {
    printf("=== Probando helpers ===\n");

    char *lower = helpers_strdup_lower("HoLa");
    if (lower == NULL || strcmp(lower, "hola") != 0) {
        fprintf(stderr, "Fallo: helpers_strdup_lower no convirtio correctamente\n");
        mm_free(lower);
        return 1;
    }

    if (!helpers_contains_case_insensitive("Lionel Messi", "mEsSi")) {
        fprintf(stderr, "Fallo: helpers_contains_case_insensitive no encontro coincidencia\n");
        mm_free(lower);
        return 1;
    }

    if (helpers_contains_case_insensitive("Lionel Messi", "maradona")) {
        fprintf(stderr, "Fallo: helpers_contains_case_insensitive encontro falso positivo\n");
        mm_free(lower);
        return 1;
    }

    mm_free(lower);
    printf("=== Fin de la prueba ===\n");
    return 0;
}
