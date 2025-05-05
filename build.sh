#!/bin/bash

# Colors
GREEN='\033[0;32m'
NC='\033[0m' # No Color

echo -e "${GREEN}Compilando proyecto...${NC}"

# Crear carpeta build si no existe
mkdir -p build

# Compilar todos los .cpp dentro de src/
g++ -std=c++17 -Iinclude -o build/main $(find src -name "*.cpp") -lGL -lGLU -lglut -lGLEW -lpthread

# Verifica si la compilación fue exitosa
if [ $? -eq 0 ]; then
    echo -e "${GREEN}Compilación exitosa. Ejecuta con: ./build/main${NC}"
else
    echo -e "\033[0;31mError en la compilación.\033[0m"
fi
