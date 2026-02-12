#ifndef COMMANDS_H
#define COMMANDS_H

// Prototipos de comandos expuestos por la shell.
int cmd_listar(char **args);
int cmd_leer(char **args);
int cmd_tiempo(char **args);
int cmd_calc(char **args);
int cmd_salir(char **args);
int comando_crear(char **args);
int comando_eliminar(char **args);
int comando_renombrar(char **args);
int comando_buscar(char **args);

#endif
