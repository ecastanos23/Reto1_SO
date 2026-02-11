# Referencia de la API Interna

## Módulo: Parser (`parser.h`)
### `char **parse_input(char *line)`
- **Descripción**: Divide una cadena en tokens usando delimitadores (espacio, tab, etc.).
- **Retorno**: Arreglo de punteros finalizado en `NULL`. Debe ser liberado con `free()`.

## Módulo: Memory Manager (`utils.h`)
### `char *mm_strdup(const char *s)`
- **Descripción**: Duplica una cadena de forma segura.
- **Importante**: Registra la asignación para el control de fugas.

## Módulo: Error Handler (`utils.h`)
### `void err_errno(const char *contexto)`
- **Descripción**: Captura el valor de `errno` y despliega un mensaje descriptivo prefijado por el contexto (ej: "EAFITos: crear: archivo ya existe").