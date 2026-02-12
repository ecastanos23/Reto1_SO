#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

// Manejo centralizado de errores y escritura opcional a archivo de log.
static FILE *err_log = NULL;

// Escribe una linea de error a stderr y al log si esta configurado.
static void err_write_line(const char *line) {
	fprintf(stderr, "%s\n", line);
	if (err_log != NULL) {
		fprintf(err_log, "%s\n", line);
		fflush(err_log);
	}
}

// Configura el archivo de log para errores; si falla, deja stderr como salida principal.
int err_set_log_file(const char *path) {
	if (path == NULL || path[0] == '\0') {
		return 0;
	}

	FILE *file = fopen(path, "a");
	if (file == NULL) {
		fprintf(stderr, "error: no se pudo abrir log '%s': %s\n", path, strerror(errno));
		return -1;
	}

	if (err_log != NULL) {
		fclose(err_log);
	}
	err_log = file;
	return 0;
}

// Cierra el log si esta abierto.
void err_close_log(void) {
	if (err_log != NULL) {
		fclose(err_log);
		err_log = NULL;
	}
}

// Escribe un mensaje de error libre con contexto opcional.
void err_message(const char *context, const char *message) {
	const char *ctx = (context == NULL || context[0] == '\0') ? "error" : context;
	const char *msg = (message == NULL) ? "" : message;
	char buffer[512];
	snprintf(buffer, sizeof(buffer), "%s: %s", ctx, msg);
	err_write_line(buffer);
}

// Escribe el error asociado a errno con un contexto opcional.
void err_errno(const char *context) {
	const char *ctx = (context == NULL || context[0] == '\0') ? "error" : context;
	char buffer[512];
	snprintf(buffer, sizeof(buffer), "%s: %s", ctx, strerror(errno));
	err_write_line(buffer);
}

// Reporta errno y termina el programa con el codigo indicado.
void err_exit_errno(const char *context, int code) {
	err_errno(context);
	exit(code);
}
