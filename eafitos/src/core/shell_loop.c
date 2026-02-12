#include <stdio.h>
#include <stdlib.h>
#include "shell.h" 
#include "utils.h"

// Bucle principal: lee la entrada, parsea y despacha comandos.
void shell_loop() {
    char linea[1024];
    char **args;
    int estado = 1;

    do {
        // Prompt y lectura de linea completa.
        printf("EAFITos > "); // Prompt personalizado
        
        if (fgets(linea, sizeof(linea), stdin) == NULL) {
            break; // Manejo de Ctrl+D
        }

        // Parseo y ejecucion del comando solicitado.
        args = parsear_linea(linea);
        
        if (args[0] != NULL) {
            estado = ejecutar_comando(args); // Función que decidirá qué comando llamar
        }

        // Liberacion de recursos del parser.
        mm_free(args); // Liberar memoria para evitar leaks
    } while (estado);
}
