#include <stdio.h>
#include "commands.h"

int main(void) {
    // Prueba simple del comando listar.
    printf("=== Probando cmd_listar ===\n");
    cmd_listar(NULL);
    printf("=== Fin de la prueba ===\n");
    return 0;
}
