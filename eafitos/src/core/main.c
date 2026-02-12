#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include "shell.h"
#include "utils.h"

int main() {
   
    // Configura el shell para IGNORAR el Ctrl+C (SIGINT)
    signal(SIGINT, SIG_IGN);

     // Bloque de bienvenida e inicializacion del entorno.
    printf("\n");
    printf("\033[1;36m============================================\033[0m\n");
    printf("\033[1;36m   \033[1;32mBienvenido a EAFITos - Shell v1.0\033[1;36m      \033[0m\n");
    printf("\033[1;36m============================================\033[0m\n");
    printf("\n");
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