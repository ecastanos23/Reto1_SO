#include <stdio.h>
#include <unistd.h>

#include "commands.h"

int main(void) {
    const char *ruta = "tmp_eliminar_test.txt";
    FILE *archivo = fopen(ruta, "w");

    printf("=== Probando comando_eliminar ===\n");

    if (archivo == NULL) {
        perror("test_eliminar");
        return 1;
    }
    fclose(archivo);

    char *args[] = {"eliminar", (char *)ruta, NULL};
    if (comando_eliminar(args) != 1) {
        fprintf(stderr, "Fallo: comando_eliminar no devolvio 1\n");
        return 1;
    }

    if (access(ruta, F_OK) == 0) {
        fprintf(stderr, "Fallo: el archivo no fue eliminado\n");
        return 1;
    }

    printf("=== Fin de la prueba ===\n");
    return 0;
}
