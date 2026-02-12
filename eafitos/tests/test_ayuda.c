#include <stdio.h>

#include "shell.h"

int main(void) {
    // Prueba de salida del comando ayuda.
    printf("=== Probando cmd_ayuda ===\n");
    cmd_ayuda(NULL);
    printf("=== Fin de la prueba ===\n");
    return 0;
}
