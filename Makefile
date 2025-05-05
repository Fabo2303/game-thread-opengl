# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -std=c++17 -Iinclude

# Output
BUILD_DIR = build
BIN = $(BUILD_DIR)/main

# Source files
SRC_DIR = src
SRCS = $(shell find $(SRC_DIR) -name '*.cpp')
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

# Libraries
LIBS = -lGL -lGLU -lglut -lGLEW -lpthread

# Default target
all: $(BIN)

# Create binary
$(BIN): $(OBJS)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LIBS)

# Create build objects
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
