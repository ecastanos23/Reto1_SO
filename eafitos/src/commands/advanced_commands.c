#include <stdio.h>
#include <string.h>

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

int comando_renombrar(char **args) {
	if (args == NULL || args[1] == NULL || args[2] == NULL) {
		fprintf(stderr, "Uso: renombrar <origen> <destino>\n");
		return 1;
	}

	if (rename(args[1], args[2]) != 0) {
		perror("renombrar");
		return 1;
	}

	return 1;
}
//uso: renombrar <original> <nuevo>

int comando_buscar(char **args) {
	if (args == NULL || args[1] == NULL || args[2] == NULL) {
		fprintf(stderr, "Uso: buscar <texto> <archivo>\n");
		return 1;
	}

	FILE *archivo = fopen(args[2], "r");
	if (archivo == NULL) {
		perror("buscar");
		return 1;
	}

	char linea[1024];
	int numero_linea = 1;
	int coincidencias = 0;

	while (fgets(linea, sizeof(linea), archivo) != NULL) {
		if (strstr(linea, args[1]) != NULL) {
			printf("%d: %s", numero_linea, linea);
			coincidencias++;
		}
		numero_linea++;
	}

	if (coincidencias == 0) {
		printf("No se encontraron coincidencias para '%s' en %s\n", args[1], args[2]);
	}

	fclose(archivo);
	return 1;
}
//uso: buscar <texto> <archivo>








