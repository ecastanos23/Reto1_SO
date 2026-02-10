#include <stdio.h>

#include "commands.h"

int comando_crear(char **args) {
	if (args == NULL || args[1] == NULL) {
		fprintf(stderr, "Uso: crear <archivo>\n");
		return 1;
	}

	FILE *archivo = fopen(args[1], "w");
	if (archivo == NULL) {
		perror("crear");
		return 1;
	}

	fclose(archivo);
	return 0;
}
