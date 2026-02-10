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
	return 1;
}

// crear un archivo con nombre distinto: cd /workspaces/Reto1_SO/eafitos touch REYES

int comando_eliminar(char **args) {
	if (args == NULL || args[1] == NULL) {
		fprintf(stderr, "Uso: eliminar <archivo>\n");
		return 1;
	}

	if (remove(args[1]) != 0) {
		perror("eliminar");
		return 1;
	}

	return 1;
}


