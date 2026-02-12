#include <stdio.h>
#include <string.h>
#include "shell.h"
#include "commands.h"

// Tabla central que relaciona nombre, funcion y descripcion del comando.
/* Tabla de comandos disponibles */
Comando comandos[] = {
    {"listar", cmd_listar, "Lista los archivos del directorio actual"},
    {"leer", cmd_leer, "Lee el contenido de un archivo"},
    {"tiempo", cmd_tiempo, "Muestra la fecha y hora actual"},
    {"calc", cmd_calc, "Calculadora basica (uso: calc num1 op num2)"},
    {"crear", comando_crear, "Crea un archivo vacio"},
    {"eliminar", comando_eliminar, "Elimina un archivo"},
    {"renombrar", comando_renombrar, "Renombra un archivo"},
    {"buscar", comando_buscar, "Busca texto en un archivo (uso: buscar <texto> <archivo>)"},
    {"ayuda", cmd_ayuda, "Muestra esta ayuda"},
    {"salir", cmd_salir, "Termina la shell EAFITos"},
    {NULL, NULL, NULL}
};

// Despacha la ejecucion al comando que coincide con el nombre ingresado.
int ejecutar_comando(char **args) {
    if (args[0] == NULL) {
        return 1;
    }

    for (int i = 0; comandos[i].nombre != NULL; i++) {
        if (strcmp(args[0], comandos[i].nombre) == 0) {
            return comandos[i].funcion(args);
        }
    }

    fprintf(stderr, "Comando no reconocido: %s\n", args[0]);
    fprintf(stderr, "Escribe 'ayuda' para ver los comandos disponibles.\n");
    return 1;
}

// Muestra la lista de comandos disponibles con su descripcion.
int cmd_ayuda(char **args) {
    (void)args;
    printf("\nComandos disponibles en EAFITos:\n");
    printf("--------------------------------\n");
    for (int i = 0; comandos[i].nombre != NULL; i++) {
        printf("  %-12s - %s\n", comandos[i].nombre, comandos[i].descripcion);
    }
    printf("\n");
    return 1;
}
