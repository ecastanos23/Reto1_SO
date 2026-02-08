#ifndef SHELL_H
#define SHELL_H

/* Definición de la estructura de comando */
typedef struct {
    char *nombre;
    int (*funcion)(char **args);
    char *descripcion;
} Comando;

/* Prototipos de funciones globales */
void loop_shell(void);
int ejecutar_comando(char **args);

#endif
