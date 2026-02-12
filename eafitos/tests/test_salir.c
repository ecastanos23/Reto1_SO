#include <stdio.h>
#include "commands.h"

int main(void) {
    int resultado;

    // Prueba de salida controlada del comando salir.
    printf("=== Probando cmd_salir ===\n");
    
    resultado = cmd_salir(NULL);
    
    // Verifica el codigo de retorno esperado.
    printf("=== Verificando resultado ===\n");
    if (resultado == 0) {
        printf("PASS: cmd_salir retorna 0 (termina la shell correctamente)\n");
    } else {
        printf("FAIL: cmd_salir retorna %d (deberia retornar 0)\n", resultado);
    }
    
    printf("=== Fin de la prueba ===\n");
    return (resultado == 0) ? 0 : 1;
}
