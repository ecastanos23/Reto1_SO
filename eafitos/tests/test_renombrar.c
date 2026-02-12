#include <stdio.h>
#include <unistd.h>

#include "commands.h"

int main(void) {
    const char *origen = "tmp_renombrar_origen.txt";
    const char *destino = "tmp_renombrar_destino.txt";
    FILE *archivo = fopen(origen, "w");

    // Prueba de renombrado de archivo temporal.
    printf("=== Probando comando_renombrar ===\n");

    // Prepara el archivo de origen.
    if (archivo == NULL) {
        perror("test_renombrar");
        return 1;
    }
    fclose(archivo);

    // Asegura que el destino no exista antes de la prueba.
    remove(destino);

    // Ejecuta el comando y valida retorno.
    char *args[] = {"renombrar", (char *)origen, (char *)destino, NULL};
    if (comando_renombrar(args) != 1) {
        fprintf(stderr, "Fallo: comando_renombrar no devolvio 1\n");
        return 1;
    }

    // Verifica que el renombrado se haya aplicado correctamente.
    if (access(destino, F_OK) != 0 || access(origen, F_OK) == 0) {
        fprintf(stderr, "Fallo: el archivo no fue renombrado correctamente\n");
        return 1;
    }

    remove(destino);
    printf("=== Fin de la prueba ===\n");
    return 0;
}
