# Variables de compilación
CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -g
SRC_DIR = src
OBJ_DIR = build
TARGET = EAFITos

# Encuentra todos los archivos .c en src/
SRCS = $(wildcard $(SRC_DIR)/*.c)
# Cambia la extensión .c por .o y los mueve a build/
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Regla principal: Compilar el ejecutable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

# Regla para compilar archivos objeto (.o)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Limpiar archivos temporales
clean:
	rm -rf $(OBJ_DIR) $(TARGET)