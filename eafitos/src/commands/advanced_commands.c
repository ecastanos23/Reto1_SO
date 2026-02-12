#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "commands.h"
#include "utils.h"

// Comando que crea un archivo vacio en la ruta indicada.
int comando_crear(char **args) {
	if (args != NULL && args[1] != NULL && strcmp(args[1], "--help") == 0) {
		printf("crear - Crea un archivo vacio en la ruta indicada.\n");
		printf("\nDescripcion:\n");
		printf("  Genera un archivo nuevo en la ruta indicada usando el nombre\n");
		printf("  proporcionado. Es util para crear placeholders o archivos\n");
		printf("  iniciales antes de editar su contenido.\n");
		printf("\nUso:\n  crear <archivo> [--help]\n");
		printf("\nNotas:\n");
		printf("  - Si el archivo existe, su contenido se sobrescribe.\n");
		printf("  - Requiere permisos de escritura en el directorio.\n");
		return 1;
	}

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

// Comando que elimina un archivo existente.
int comando_eliminar(char **args) {
	if (args != NULL && args[1] != NULL && strcmp(args[1], "--help") == 0) {
		printf("eliminar - Elimina un archivo existente.\n");
		printf("\nDescripcion:\n");
		printf("  Borra el archivo indicado del sistema de archivos. Esta accion\n");
		printf("  es directa y no mueve el archivo a ningun lugar de recuperacion,\n");
		printf("  por lo que debe usarse con cuidado.\n");
		printf("\nUso:\n  eliminar <archivo> [--help]\n");
		printf("\nNotas:\n");
		printf("  - La eliminacion es permanente.\n");
		printf("  - Requiere permisos sobre el archivo.\n");
		return 1;
	}

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

// Comando que renombra un archivo de origen a destino.
int comando_renombrar(char **args) {
	if (args != NULL && args[1] != NULL && strcmp(args[1], "--help") == 0) {
		printf("renombrar - Cambia el nombre de un archivo.\n");
		printf("\nDescripcion:\n");
		printf("  Renombra un archivo existente indicando un nombre de origen y\n");
		printf("  otro de destino. Sirve para organizar archivos sin necesidad de\n");
		printf("  recrearlos o copiarlos.\n");
		printf("\nUso:\n  renombrar <origen> <destino> [--help]\n");
		printf("\nNotas:\n");
		printf("  - Si el destino existe, puede sobrescribirse segun el sistema.\n");
		printf("  - Requiere permisos sobre ambos nombres.\n");
		return 1;
	}

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


// Comando que busca texto (case-insensitive) dentro de un archivo.
int comando_buscar(char **args) {
	if (args != NULL && args[1] != NULL && strcmp(args[1], "--help") == 0) {
		printf("buscar - Busca texto dentro de un archivo.\n");
		printf("\nDescripcion:\n");
		printf("  Recorre el archivo linea por linea y muestra aquellas que\n");
		printf("  contienen el texto indicado, sin distinguir mayusculas de\n");
		printf("  minusculas. Permite buscar frases con varias palabras.\n");
		printf("\nUso:\n  buscar <texto...> <archivo> [--help]\n");
		printf("\nNotas:\n");
		printf("  - La busqueda no distingue mayusculas/minusculas.\n");
		printf("  - Puede usar varias palabras en <texto...>.\n");
		return 1;
	}

	if (args == NULL || args[1] == NULL || args[2] == NULL) {
		fprintf(stderr, "Uso: buscar <texto...> <archivo>\n");
		return 1;
	}

    // Detecta el ultimo argumento para separar texto y nombre de archivo.
	int last = 0;
	while (args[last] != NULL) {
		last++;
	}

	if (last < 3) {
		fprintf(stderr, "Uso: buscar <texto...> <archivo>\n");
		return 1;
	}

    // Reconstruye el texto de busqueda a partir de los argumentos.
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

    // Recorre el archivo y reporta las lineas que coinciden.
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








