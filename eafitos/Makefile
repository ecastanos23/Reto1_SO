CC = gcc
# -g es vital para que el Tester use Valgrind y detecte memory leaks (-10 pts si los hay)
CFLAGS = -Wall -Wextra -Iinclude -g
SRC_DIR = src
OBJ_DIR = build

# Encuentra todos los archivos .c
SRCS = $(shell find $(SRC_DIR) -name '*.c')
# Genera los nombres de los .o manteniendo la estructura de carpetas
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

TARGET = EAFITos

# PHONY evita conflictos si existen archivos llamados 'clean' o 'all'
.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Regla de compilación: crea la carpeta build si no existe
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(TARGET)