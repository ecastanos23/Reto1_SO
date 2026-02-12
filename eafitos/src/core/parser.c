#include <stdlib.h>
#include <string.h>

#include "parser.h"
#include "utils.h"

// Convierte una linea en un arreglo de tokens segun delimitadores del parser.
ParserResult parser_parse_line(char *linea) {
    ParserResult res;
    res.args = NULL;
    res.argc = 0;
    res.status = PARSER_OK;

    if (linea == NULL || linea[0] == '\0') {
        res.status = PARSER_ERR_EMPTY;
        return res;
    }

    char **tokens = mm_malloc(PARSER_MAX_ARGS * sizeof(char *));
    if (tokens == NULL) {
        res.status = PARSER_ERR_OOM;
        return res;
    }

    int posicion = 0;
    char *token = strtok(linea, PARSER_DELIM);
    while (token != NULL && posicion < (PARSER_MAX_ARGS - 1)) {
        tokens[posicion] = token;
        posicion++;
        token = strtok(NULL, PARSER_DELIM);
    }
    // El ultimo debe ser NULL para funciones como execvp.
    tokens[posicion] = NULL;

    res.args = tokens;
    res.argc = posicion;
    res.status = (posicion == 0) ? PARSER_ERR_EMPTY : PARSER_OK;
    return res;
}

// Libera el arreglo de argumentos generado por el parser.
void parser_free_result(ParserResult *res) {
    if (res == NULL || res->args == NULL) {
        return;
    }
    mm_free(res->args);
    res->args = NULL;
    res->argc = 0;
    res->status = PARSER_OK;
}

// Indica si el resultado no tiene comandos para ejecutar.
int parser_is_empty(const ParserResult *res) {
    if (res == NULL || res->args == NULL) {
        return 1;
    }
    return (res->argc == 0 || res->args[0] == NULL) ? 1 : 0;
}

// Compatibilidad: devuelve solo el arreglo de argumentos.
char **parsear_linea(char *linea) {
    ParserResult res = parser_parse_line(linea);
    return res.args;
}