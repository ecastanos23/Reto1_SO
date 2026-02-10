#include <stdio.h>

#include "shell.h"

int main(void) {
    printf("=== Probando cmd_ayuda ===\n");
    cmd_ayuda(NULL);
    printf("=== Fin de la prueba ===\n");
    return 0;
}
