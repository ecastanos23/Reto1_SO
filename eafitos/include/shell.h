#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Cabecera central de la shell: tipos, constantes y prototipos.
/* --- Constantes para el Parser --- */
#define MAX_LINE 1024
#define MAX_ARGS 64
#define DELIM " \t\r\n\a"

// Estructura que describe un comando disponible.
/* --- Definición de la estructura de comando --- */
typedef struct {
    char *nombre;
    int (*funcion)(char **args);
    char *descripcion;
} Comando;

// Prototipos del nucleo (loop, parser y dispatch).
/* --- Prototipos del Núcleo (Core) --- */
void shell_loop(void);
char **parsear_linea(char *linea); // Necesario para el parser.c
int ejecutar_comando(char **args);

// Prototipos de comandos basicos y avanzados.
/* --- Prototipos de Comandos (Para el Desarrollador) --- */
/* Básicos (Obligatorios) */
int cmd_listar(char **args);
int cmd_leer(char **args);
int cmd_tiempo(char **args);
int cmd_calc(char **args);
int cmd_ayuda(char **args);
int cmd_salir(char **args);

/* Avanzados (Elegidos por el equipo) */
int cmd_crear(char **args);
int cmd_eliminar(char **args);
int cmd_limpiar(char **args);
int cmd_directorio(char **args);

#endif