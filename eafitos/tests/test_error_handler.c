#include <stdio.h>
#include <string.h>

#include "utils.h"

int main(void) {
    const char *ruta = "tests/tmp_error_log.txt";
    const char *mensaje = "error de prueba";

    printf("=== Probando error_handler ===\n");

    if (err_set_log_file(ruta) != 0) {
        fprintf(stderr, "Fallo: no se pudo abrir log de prueba\n");
        return 1;
    }

    err_message("test", mensaje);
    err_close_log();

    FILE *archivo = fopen(ruta, "r");
    if (archivo == NULL) {
        fprintf(stderr, "Fallo: no se pudo leer log de prueba\n");
        return 1;
    }

    char buffer[256];
    int encontrado = 0;
    while (fgets(buffer, sizeof(buffer), archivo) != NULL) {
        if (strstr(buffer, mensaje) != NULL) {
            encontrado = 1;
            break;
        }
    }
    fclose(archivo);

    remove(ruta);

    if (!encontrado) {
        fprintf(stderr, "Fallo: mensaje no encontrado en el log\n");
        return 1;
    }

    printf("=== Fin de la prueba ===\n");
    return 0;
}
