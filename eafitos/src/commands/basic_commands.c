#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

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