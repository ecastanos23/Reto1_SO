#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "commands.h"
#include "utils.h"

// Comando que lista el contenido del directorio actual.
int cmd_listar(char **args) {
	DIR *dir;
	struct dirent *entry;

	(void)args;
	dir = opendir(".");
    if (!dir) {
        err_errno("listar");
		return 1;
	}

	while ((entry = readdir(dir)) != NULL) {
		if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
			continue;
		}
		printf("%s\n", entry->d_name);
	}

	closedir(dir);
	return 1;
}
// Comando que lee y muestra el contenido de un archivo de texto.
int cmd_leer(char **args) {
    FILE *archivo;
    char buffer[1024];
    char *ruta;

    if (args[1] == NULL) {
        fprintf(stderr, "leer: se requiere un argumento (nombre del archivo)\n");
        return 1;
    }

    ruta = mm_strdup(args[1]);
    archivo = fopen(ruta, "r");
    if (!archivo) {
        err_errno("leer");
        mm_free(ruta);
        return 1;
    }

    while (fgets(buffer, sizeof(buffer), archivo) != NULL) {
        printf("%s", buffer);
    }

    fclose(archivo);
    mm_free(ruta);
    return 1;
}

// Comando que imprime la fecha y hora actual.
int cmd_tiempo(char **args) {
    time_t ahora;
    struct tm *info_tiempo;
    char buffer[80];

    (void)args;
    time(&ahora);
    info_tiempo = localtime(&ahora);

    strftime(buffer, sizeof(buffer), "%d/%m/%Y %H:%M:%S", info_tiempo);
    printf("Fecha y hora actual: %s\n", buffer);

    return 1;
}

// Comando de calculadora basica con operador binario.
int cmd_calc(char **args) {
    double num1, num2, resultado;
    char operador;
    char *num1_str;
    char *op_str;
    char *num2_str;

    if (args[1] == NULL || args[2] == NULL || args[3] == NULL) {
        fprintf(stderr, "calc: uso: calc <num1> <operador> <num2>\n");
        fprintf(stderr, "      operadores: + - * /\n");
        return 1;
    }

    num1_str = mm_strdup(args[1]);
    op_str = mm_strdup(args[2]);
    num2_str = mm_strdup(args[3]);

    num1 = atof(num1_str);
    operador = op_str[0];
    num2 = atof(num2_str);

    switch (operador) {
        case '+':
            resultado = num1 + num2;
            break;
        case '-':
            resultado = num1 - num2;
            break;
        case '*':
            resultado = num1 * num2;
            break;
        case '/':
            if (num2 == 0) {
                fprintf(stderr, "calc: error: division por cero\n");
                mm_free(num1_str);
                mm_free(op_str);
                mm_free(num2_str);
                return 1;
            }
            resultado = num1 / num2;
            break;
        default:
            fprintf(stderr, "calc: operador '%c' no reconocido\n", operador);
            fprintf(stderr, "      operadores validos: + - * /\n");
            mm_free(num1_str);
            mm_free(op_str);
            mm_free(num2_str);
            return 1;
    }

    printf("%.2f %c %.2f = %.2f\n", num1, operador, num2, resultado);
    mm_free(num1_str);
    mm_free(op_str);
    mm_free(num2_str);
    return 1;
}

// Comando para salir del bucle principal de la shell.
int cmd_salir(char **args) {
    (void)args;
    printf("Saliendo de EAFITos... ¡Hasta pronto!\n");
    return 0;
}