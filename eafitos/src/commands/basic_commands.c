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

    if (args[1] != NULL && strcmp(args[1], "--help") == 0) {
        printf("listar - Lista los archivos del directorio actual.\n");
        printf("\nDescripcion:\n");
        printf("  Muestra de forma simple los nombres de los archivos y carpetas que\n");
        printf("  existen en el directorio actual, omitiendo las entradas especiales.\n");
        printf("\nUso:\n  listar [--help]\n");
        printf("\nNotas:\n");
        printf("  - No muestra las entradas '.' y '..'.\n");
        printf("  - Solo lista el directorio actual.\n");
        return 1;
    }

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

    if (args[1] != NULL && strcmp(args[1], "--help") == 0) {
        printf("leer - Muestra el contenido de un archivo de texto.\n");
        printf("\nDescripcion:\n");
        printf("  Abre el archivo indicado y escribe su contenido en la salida\n");
        printf("  estandar, respetando el orden de las lineas. Es util para\n");
        printf("  inspeccionar archivos pequenos sin salir de la shell.\n");
        printf("\nUso:\n  leer <archivo> [--help]\n");
        printf("\nNotas:\n");
        printf("  - Requiere el nombre del archivo a leer.\n");
        printf("  - Si el archivo no existe, se informa el error.\n");
        return 1;
    }

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

    if (args[1] != NULL && strcmp(args[1], "--help") == 0) {
        printf("tiempo - Muestra la fecha y hora actual.\n");
        printf("\nDescripcion:\n");
        printf("  Imprime la fecha y hora del sistema local con un formato\n");
        printf("  legible, para consultar rapidamente el momento actual sin\n");
        printf("  usar comandos externos.\n");
        printf("\nUso:\n  tiempo [--help]\n");
        printf("\nNotas:\n");
        printf("  - Formato: DD/MM/AAAA HH:MM:SS\n");
        return 1;
    }

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

    if (args[1] != NULL && strcmp(args[1], "--help") == 0) {
        printf("calc - Calculadora basica.\n");
        printf("\nDescripcion:\n");
        printf("  Realiza una operacion aritmetica simple entre dos numeros usando\n");
        printf("  un operador binario. Esta pensada para calculos rapidos y evita\n");
        printf("  dependencias externas.\n");
        printf("\nUso:\n  calc <num1> <operador> <num2> [--help]\n");
        printf("\nOperadores:\n  +  -  *  /\n");
        printf("\nNotas:\n");
        printf("  - La division por cero no esta permitida.\n");
        printf("  - Los numeros se interpretan como decimales.\n");
        return 1;
    }

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
    if (args[1] != NULL && strcmp(args[1], "--help") == 0) {
        printf("salir - Termina la ejecucion de la shell.\n");
        printf("\nDescripcion:\n");
        printf("  Finaliza el bucle principal de la shell y cierra la sesion\n");
        printf("  actual. Es el metodo recomendado para salir limpiamente del\n");
        printf("  entorno EAFITos.\n");
        printf("\nUso:\n  salir [--help]\n");
        printf("\nNotas:\n");
        printf("  - Cierra la sesion de EAFITos.\n");
        return 1;
    }

    (void)args;
    printf("Saliendo de EAFITos... ¡Hasta pronto!\n");
    return 0;
}