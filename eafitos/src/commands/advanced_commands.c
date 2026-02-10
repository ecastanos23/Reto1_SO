#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "commands.h"
#include "utils.h"

int comando_crear(char **args) {
	if (args == NULL || args[1] == NULL) {
		fprintf(stderr, "Uso: crear <archivo>\n");
		return 1;
	}

	char *ruta = mm_strdup(args[1]);
	FILE *archivo = fopen(ruta, "w");
	if (archivo == NULL) {
		err_errno("crear");
		mm_free(ruta);
		return 1;
	}

	fclose(archivo);
	mm_free(ruta);
	return 1;
}

// uso en ./EAFITos: crear <archivo>

int comando_eliminar(char **args) {
	if (args == NULL || args[1] == NULL) {
		fprintf(stderr, "Uso: eliminar <archivo>\n");
		return 1;
	}

	char *ruta = mm_strdup(args[1]);
	if (remove(ruta) != 0) {
		err_errno("eliminar");
		mm_free(ruta);
		return 1;
	}
	mm_free(ruta);

	return 1;
}
//uso: eliminar <archivo>

int comando_renombrar(char **args) {
	if (args == NULL || args[1] == NULL || args[2] == NULL) {
		fprintf(stderr, "Uso: renombrar <origen> <destino>\n");
		return 1;
	}

	char *origen = mm_strdup(args[1]);
	char *destino = mm_strdup(args[2]);

	if (rename(origen, destino) != 0) {
		err_errno("renombrar");
		mm_free(origen);
		mm_free(destino);
		return 1;
	}

	mm_free(origen);
	mm_free(destino);

	return 1;
}
//uso: renombrar <original> <nuevo>


int comando_buscar(char **args) {
	if (args == NULL || args[1] == NULL || args[2] == NULL) {
		fprintf(stderr, "Uso: buscar <texto...> <archivo>\n");
		return 1;
	}

	int last = 0;
	while (args[last] != NULL) {
		last++;
	}

	if (last < 3) {
		fprintf(stderr, "Uso: buscar <texto...> <archivo>\n");
		return 1;
	}

	char *archivo_nombre = mm_strdup(args[last - 1]);
	char *texto = mm_calloc(1, 1024);

	for (int i = 1; i < last - 1; i++) {
		if (i > 1) {
			strncat(texto, " ", 1024 - strlen(texto) - 1);
		}
		strncat(texto, args[i], 1024 - strlen(texto) - 1);
	}

	FILE *archivo = fopen(archivo_nombre, "r");
	if (archivo == NULL) {
		err_errno("buscar");
		mm_free(texto);
		mm_free(archivo_nombre);
		return 1;
	}

	char linea[1024];
	int numero_linea = 1;
	int coincidencias = 0;

	while (fgets(linea, sizeof(linea), archivo) != NULL) {
		if (helpers_contains_case_insensitive(linea, texto)) {
			printf("%d: %s", numero_linea, linea);
			coincidencias++;
		}
		numero_linea++;
	}

	if (coincidencias == 0) {
		printf("No se encontraron coincidencias para '%s' en %s\n", texto, archivo_nombre);
	}

	fclose(archivo);
	mm_free(texto);
	mm_free(archivo_nombre);
	return 1;
}
//uso: buscar <texto> <archivo>








