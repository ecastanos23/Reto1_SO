#include <stdio.h>
#include <unistd.h>

#include "commands.h"

int main(void) {
    const char *ruta = "tests/jugadores.txt";

    printf("=== Probando comando_buscar ===\n");

    if (access(ruta, F_OK) != 0) {
        fprintf(stderr, "Fallo: no existe el archivo de prueba %s\n", ruta);
        return 1;
    }

    char *args[] = {"buscar", "lIoNeL", "mEsSi", (char *)ruta, NULL};
    comando_buscar(args);

    printf("=== Fin de la prueba ===\n");
    return 0;
}
