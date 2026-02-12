// API del parser: tokenizacion de linea y manejo basico de errores.
#ifndef PARSER_H
#define PARSER_H

// Constantes del parser para limites y delimitadores de tokens.
#define PARSER_MAX_LINE 1024
#define PARSER_MAX_ARGS 64
#define PARSER_DELIM " \t\r\n\a"

// Estados de salida del parser para distinguir casos comunes.
typedef enum {
	PARSER_OK = 0,
	PARSER_ERR_EMPTY = 1,
	PARSER_ERR_OOM = 2
} ParserStatus;

// Resultado del parser: arreglo de argumentos y contador.
typedef struct {
	char **args;
	int argc;
	ParserStatus status;
} ParserResult;

// Convierte una linea en tokens listos para ejecutar comandos.
ParserResult parser_parse_line(char *linea);

// Libera los recursos asociados al resultado del parser.
void parser_free_result(ParserResult *res);

// Indica si el resultado es vacio o invalido para ejecutar.
int parser_is_empty(const ParserResult *res);

#endif
