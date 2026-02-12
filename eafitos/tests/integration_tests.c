// Pruebas de integracion: ejecuta una secuencia de comandos en conjunto.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "commands.h"
#include "utils.h"

int main(void) {
	const char *ruta = "tests/tmp_integracion.txt";
	const char *ruta_ren = "tests/tmp_integracion_renombrado.txt";

	// Inicializacion de utilidades globales (memoria y errores).
	mm_init();
	err_set_log_file("tests/tmp_integracion_error.log");
	atexit(err_close_log);
	atexit(mm_cleanup);
	atexit(mm_report);

	// Preparacion del entorno: elimina restos de ejecuciones previas.
	remove(ruta);
	remove(ruta_ren);

	printf("=== Prueba de integracion ===\n");

	// Bloque: crear archivo base.
	char *args_crear[] = {"crear", (char *)ruta, NULL};
	if (comando_crear(args_crear) != 1) {
		fprintf(stderr, "Fallo: comando_crear no devolvio 1\n");
		return 1;
	}

	// Bloque: escribir contenido para pruebas de lectura/busqueda.
	FILE *archivo = fopen(ruta, "w");
	if (archivo == NULL) {
		perror("integration_tests");
		return 1;
	}
	fprintf(archivo, "Lionel Messi\n");
	fprintf(archivo, "EAFITos integration test\n");
	fclose(archivo);

	// Bloque: leer contenido del archivo.
	char *args_leer[] = {"leer", (char *)ruta, NULL};
	if (cmd_leer(args_leer) != 1) {
		fprintf(stderr, "Fallo: cmd_leer no devolvio 1\n");
		return 1;
	}

	// Bloque: buscar texto dentro del archivo.
	char *args_buscar[] = {"buscar", "messi", (char *)ruta, NULL};
	if (comando_buscar(args_buscar) != 1) {
		fprintf(stderr, "Fallo: comando_buscar no devolvio 1\n");
		return 1;
	}

	// Bloque: renombrar archivo y validar existencia.
	char *args_renombrar[] = {"renombrar", (char *)ruta, (char *)ruta_ren, NULL};
	if (comando_renombrar(args_renombrar) != 1) {
		fprintf(stderr, "Fallo: comando_renombrar no devolvio 1\n");
		return 1;
	}
	if (access(ruta_ren, F_OK) != 0) {
		fprintf(stderr, "Fallo: archivo renombrado no existe\n");
		return 1;
	}

	// Bloque: ejecutar comandos informativos basicos.
	char *args_listar[] = {"listar", NULL};
	if (cmd_listar(args_listar) != 1) {
		fprintf(stderr, "Fallo: cmd_listar no devolvio 1\n");
		return 1;
	}
	char *args_tiempo[] = {"tiempo", NULL};
	if (cmd_tiempo(args_tiempo) != 1) {
		fprintf(stderr, "Fallo: cmd_tiempo no devolvio 1\n");
		return 1;
	}

	// Bloque: eliminar archivo y validar limpieza.
	char *args_eliminar[] = {"eliminar", (char *)ruta_ren, NULL};
	if (comando_eliminar(args_eliminar) != 1) {
		fprintf(stderr, "Fallo: comando_eliminar no devolvio 1\n");
		return 1;
	}
	if (access(ruta_ren, F_OK) == 0) {
		fprintf(stderr, "Fallo: el archivo no fue eliminado\n");
		return 1;
	}

	printf("=== Fin de la prueba ===\n");
	return 0;
}
