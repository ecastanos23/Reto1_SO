#include <stdio.h>
#include <string.h>
#include "commands.h"

int main(void) {
    char num1[50], operador[10], num2[50];

    // Prueba interactiva del comando calc.
    printf("=== Calculadora Interactiva ===\n");
    printf("Ingrese: <num1> <operador> <num2>\n");
    printf("Ejemplo: 10 + 5\n");
    printf("> ");

    // Simula el argumento de linea para reutilizar cmd_calc.
    if (scanf("%s %s %s", num1, operador, num2) == 3) {
        char *args[] = {"calc", num1, operador, num2, NULL};
        cmd_calc(args);
    } else {
        printf("Error: entrada invalida\n");
    }

    printf("=== Fin de la prueba ===\n");
    return 0;
}
