#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "commands.h"

int cmd_listar(char **args) {
	DIR *dir;
	struct dirent *entry;

	(void)args;
	dir = opendir(".");
	if (!dir) {
		fprintf(stderr, "listar: no se pudo abrir el directorio actual: %s\n", strerror(errno));
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
int cmd_leer(char **args) {
    FILE *archivo;
    char buffer[1024];

    if (args[1] == NULL) {
        fprintf(stderr, "leer: se requiere un argumento (nombre del archivo)\n");
        return 1;
    }

    archivo = fopen(args[1], "r");
    if (!archivo) {
        fprintf(stderr, "leer: no se pudo abrir '%s': %s\n", args[1], strerror(errno));
        return 1;
    }

    while (fgets(buffer, sizeof(buffer), archivo) != NULL) {
        printf("%s", buffer);
    }

    fclose(archivo);
    return 1;
}

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

int cmd_calc(char **args) {
    double num1, num2, resultado;
    char operador;

    if (args[1] == NULL || args[2] == NULL || args[3] == NULL) {
        fprintf(stderr, "calc: uso: calc <num1> <operador> <num2>\n");
        fprintf(stderr, "      operadores: + - * /\n");
        return 1;
    }

    num1 = atof(args[1]);
    operador = args[2][0];
    num2 = atof(args[3]);

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
                return 1;
            }
            resultado = num1 / num2;
            break;
        default:
            fprintf(stderr, "calc: operador '%c' no reconocido\n", operador);
            fprintf(stderr, "      operadores validos: + - * /\n");
            return 1;
    }

    printf("%.2f %c %.2f = %.2f\n", num1, operador, num2, resultado);
    return 1;
}