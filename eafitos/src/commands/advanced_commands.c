#include <ctype.h>
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

static int contiene_ignorar_mayusculas(const char *linea, const char *texto) {
	if (linea == NULL || texto == NULL || texto[0] == '\0') {
		return 0;
	}

	size_t texto_len = strlen(texto);

	for (size_t i = 0; linea[i] != '\0'; i++) {
		size_t j = 0;
		while (texto[j] != '\0' && linea[i + j] != '\0') {
			unsigned char c1 = (unsigned char)linea[i + j];
			unsigned char c2 = (unsigned char)texto[j];
			if (tolower(c1) != tolower(c2)) {
				break;
			}
			j++;
		}
		if (j == texto_len) {
			return 1;
		}
	}

	return 0;
}

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

	const char *archivo_nombre = args[last - 1];
	char texto[1024];
	texto[0] = '\0';

	for (int i = 1; i < last - 1; i++) {
		if (i > 1) {
			strncat(texto, " ", sizeof(texto) - strlen(texto) - 1);
		}
		strncat(texto, args[i], sizeof(texto) - strlen(texto) - 1);
	}

	FILE *archivo = fopen(archivo_nombre, "r");
	if (archivo == NULL) {
		perror("buscar");
		return 1;
	}

	char linea[1024];
	int numero_linea = 1;
	int coincidencias = 0;

	while (fgets(linea, sizeof(linea), archivo) != NULL) {
		if (contiene_ignorar_mayusculas(linea, texto)) {
			printf("%d: %s", numero_linea, linea);
			coincidencias++;
		}
		numero_linea++;
	}

	if (coincidencias == 0) {
		printf("No se encontraron coincidencias para '%s' en %s\n", texto, archivo_nombre);
	}

	fclose(archivo);
	return 1;
}
//uso: buscar <texto> <archivo>








