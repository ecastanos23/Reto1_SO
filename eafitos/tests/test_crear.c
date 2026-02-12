#include <stdio.h>
#include <unistd.h>

#include "commands.h"

int main(void) {
    const char *ruta = "tmp_crear_test.txt";
    char *args[] = {"crear", (char *)ruta, NULL};

    // Prueba de creacion de archivo temporal.
    printf("=== Probando comando_crear ===\n");
    if (comando_crear(args) != 0) {
        fprintf(stderr, "Fallo: comando_crear devolvio error\n");
        return 1;
    }

    // Verifica que el archivo exista tras ejecutar el comando.
    if (access(ruta, F_OK) != 0) {
        fprintf(stderr, "Fallo: el archivo no fue creado\n");
        return 1;
    }

    // Limpieza del archivo temporal.
    remove(ruta);
    printf("=== Fin de la prueba ===\n");
    return 0;
}
