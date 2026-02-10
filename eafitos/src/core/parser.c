#include <string.h>
#include <stdlib.h>

#define MAX_ARGS 64
#define DELIM " \t\r\n\a"

char **parsear_linea(char *linea) {
    int bufsize = MAX_ARGS;
    int posicion = 0;
    char **tokens = malloc(bufsize * sizeof(char*));
    char *token;

    if (!tokens) {
        exit(EXIT_FAILURE); // Error de asignación de memoria
    }

    token = strtok(linea, DELIM);
    while (token != NULL) {
        tokens[posicion] = token;
        posicion++;

        token = strtok(NULL, DELIM);
    }
    tokens[posicion] = NULL; // El último debe ser NULL para funciones como execvp
    return tokens;
}