#include <stdio.h>
#include "commands.h"

int main(void) {
    // Prueba de impresion de fecha y hora.
    printf("=== Probando cmd_tiempo ===\n");
    cmd_tiempo(NULL);
    printf("=== Fin de la prueba ===\n");
    return 0;
}
