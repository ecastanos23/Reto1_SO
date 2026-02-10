#include <stdio.h>
#include <stdlib.h>
#include "shell.h" // Aquí estarán tus prototipos
#include "utils.h"

void shell_loop() {
    char linea[1024];
    char **args;
    int estado = 1;

    do {
        printf("EAFITos > "); // Prompt personalizado
        
        if (fgets(linea, sizeof(linea), stdin) == NULL) {
            break; // Manejo de Ctrl+D
        }

        args = parsear_linea(linea);
        
        if (args[0] != NULL) {
            estado = ejecutar_comando(args); // Función que decidirá qué comando llamar
        }

        mm_free(args); // Liberar memoria para evitar leaks
    } while (estado);
}