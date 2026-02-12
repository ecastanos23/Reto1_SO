#include <stdio.h>
#include <unistd.h>

#include "commands.h"

int main(void) {
    const char *ruta = "tests/jugadores.txt";

    // Prueba de busqueda con texto compuesto.
    printf("=== Probando comando_buscar ===\n");

    // Verifica precondicion: archivo de prueba disponible.
    if (access(ruta, F_OK) != 0) {
        fprintf(stderr, "Fallo: no existe el archivo de prueba %s\n", ruta);
        return 1;
    }

    // Ejecuta el comando con palabras en mayusculas mixtas.
    char *args[] = {"buscar", "lIoNeL", "mEsSi", (char *)ruta, NULL};
    comando_buscar(args);

    printf("=== Fin de la prueba ===\n");
    return 0;
}
