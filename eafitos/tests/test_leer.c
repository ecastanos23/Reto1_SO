#include <stdio.h>
#include "commands.h"

int main(void) {
    printf("=== Probando cmd_leer ===\n");
    char *args_leer[] = {"leer", "README.md", NULL};
    cmd_leer(args_leer);
    printf("=== Fin de la prueba ===\n");
    return 0;
}
