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

// uso en ./EAFITos: crear <archivo>

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
//uso: eliminar <archivo>

int comando_mover(char **args) {
	if (args == NULL || args[1] == NULL || args[2] == NULL) {
		fprintf(stderr, "Uso: mover <origen> <destino>\n");
		return 1;
	}

	if (rename(args[1], args[2]) != 0) {
		perror("mover");
		return 1;
	}

	return 1;
}






