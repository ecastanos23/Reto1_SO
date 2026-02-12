#include <stdio.h>
#include <stdlib.h>
#include "shell.h"
#include "utils.h"

int main() {
    // Bloque de bienvenida e inicializacion del entorno.
    printf("------------------------------------------\n");
    printf("   Bienvenido a EAFITos - Shell v1.0      \n");
    printf("------------------------------------------\n");
    // Registro de utilidades globales (memoria y errores).
    mm_init();
    err_set_log_file("eafitos_error.log");
    atexit(err_close_log);
    atexit(mm_cleanup);
    atexit(mm_report);
    // Transferencia de control al bucle principal de la shell.
    //Función de shell_loop
    shell_loop();
    return 0;
}