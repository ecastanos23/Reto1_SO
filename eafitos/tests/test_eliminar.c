#include <stdio.h>
#include <unistd.h>

#include "commands.h"

int main(void) {
    const char *ruta = "tmp_eliminar_test.txt";
    FILE *archivo = fopen(ruta, "w");

    // Prueba de eliminacion de archivo temporal.
    printf("=== Probando comando_eliminar ===\n");

    // Prepara el archivo que sera eliminado.
    if (archivo == NULL) {
        perror("test_eliminar");
        return 1;
    }
    fclose(archivo);

    // Ejecuta el comando y valida el codigo de retorno.
    char *args[] = {"eliminar", (char *)ruta, NULL};
    if (comando_eliminar(args) != 1) {
        fprintf(stderr, "Fallo: comando_eliminar no devolvio 1\n");
        return 1;
    }

    // Confirma que el archivo ya no exista.
    if (access(ruta, F_OK) == 0) {
        fprintf(stderr, "Fallo: el archivo no fue eliminado\n");
        return 1;
    }

    printf("=== Fin de la prueba ===\n");
    return 0;
}
