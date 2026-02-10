#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

static FILE *err_log = NULL;

static void err_write_line(const char *line) {
	fprintf(stderr, "%s\n", line);
	if (err_log != NULL) {
		fprintf(err_log, "%s\n", line);
		fflush(err_log);
	}
}

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

void err_close_log(void) {
	if (err_log != NULL) {
		fclose(err_log);
		err_log = NULL;
	}
}

void err_message(const char *context, const char *message) {
	const char *ctx = (context == NULL || context[0] == '\0') ? "error" : context;
	const char *msg = (message == NULL) ? "" : message;
	char buffer[512];
	snprintf(buffer, sizeof(buffer), "%s: %s", ctx, msg);
	err_write_line(buffer);
}

void err_errno(const char *context) {
	const char *ctx = (context == NULL || context[0] == '\0') ? "error" : context;
	char buffer[512];
	snprintf(buffer, sizeof(buffer), "%s: %s", ctx, strerror(errno));
	err_write_line(buffer);
}

void err_exit_errno(const char *context, int code) {
	err_errno(context);
	exit(code);
}
