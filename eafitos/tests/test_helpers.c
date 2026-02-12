#include <stdio.h>
#include <string.h>

#include "utils.h"

int main(void) {
    // Bloque de pruebas para utilidades de texto.
    printf("=== Probando helpers ===\n");

    // Caso: conversion a minusculas.
    char *lower = helpers_strdup_lower("HoLa");
    if (lower == NULL || strcmp(lower, "hola") != 0) {
        fprintf(stderr, "Fallo: helpers_strdup_lower no convirtio correctamente\n");
        mm_free(lower);
        return 1;
    }

    // Caso: busqueda sin sensibilidad a mayusculas.
    if (!helpers_contains_case_insensitive("Lionel Messi", "mEsSi")) {
        fprintf(stderr, "Fallo: helpers_contains_case_insensitive no encontro coincidencia\n");
        mm_free(lower);
        return 1;
    }

    // Caso: rechazo de falso positivo.
    if (helpers_contains_case_insensitive("Lionel Messi", "maradona")) {
        fprintf(stderr, "Fallo: helpers_contains_case_insensitive encontro falso positivo\n");
        mm_free(lower);
        return 1;
    }

    mm_free(lower);
    printf("=== Fin de la prueba ===\n");
    return 0;
}
