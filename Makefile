CC = g++
CFLAGS = -Wall -std=c++17
INC = -Iinclude
LIBS = -lGL -lGLU -lglut -lpthread
SRC_DIR = src
BUILD_DIR = build
OBJ_DIR = build/objects
CHARACTER_OBJ_DIR = $(OBJ_DIR)/characters
UTILS_OBJ_DIR = $(OBJ_DIR)/utils

# Archivos fuente y objetos
SOURCES = $(wildcard $(SRC_DIR)/utils/*.cpp) $(wildcard $(SRC_DIR)/characters/*.cpp) $(SRC_DIR)/main.cpp
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Nombre del ejecutable
EXEC = main

# Regla para compilar el ejecutable
$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(BUILD_DIR)/$(EXEC) $(LIBS)

# Regla para compilar archivos fuente .cpp a objetos .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)  # Crea el directorio para el archivo .o
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

# Limpiar los archivos generados
clean:
	rm -rf $(OBJ_DIR)/*.o $(BUILD_DIR)/$(EXEC)

# Regla para crear el directorio principal de objetos si no existe
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
