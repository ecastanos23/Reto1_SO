#include <stdio.h>
#include <stdlib.h>
#include "shell.h"
#include "utils.h"

int main() {
    printf("------------------------------------------\n");
    printf("   Bienvenido a EAFITos - Shell v1.0      \n");
    printf("------------------------------------------\n");
    mm_init();
    atexit(mm_cleanup);
    atexit(mm_report);
    //Función de shell_loop
    shell_loop();
    return 0;
}